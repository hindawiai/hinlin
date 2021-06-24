<शैली गुरु>
 /***************************************************************************\
|*                                                                           *|
|*       Copyright 1993-1999 NVIDIA, Corporation.  All rights reserved.      *|
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
|*       Copyright 1993-1999 NVIDIA, Corporation.  All rights reserved.      *|
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
 * GPL licensing note -- nVidia is allowing a liberal पूर्णांकerpretation of
 * the करोcumentation restriction above, to merely say that this nVidia's
 * copyright and disclaimer should be included with all code derived
 * from this source.  -- Jeff Garzik <jgarzik@pobox.com>, 01/Nov/99 
 */

/* $XFree86: xc/programs/Xserver/hw/xमुक्त86/drivers/nv/riva_hw.c,v 1.33 2002/08/05 20:47:06 mvojkovi Exp $ */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश "riva_hw.h"
#समावेश "riva_tbl.h"
#समावेश "nv_type.h"

/*
 * This file is an OS-agnostic file used to make RIVA 128 and RIVA TNT
 * operate identically (except TNT has more memory and better 3D quality.
 */
अटल पूर्णांक nv3Busy
(
    RIVA_HW_INST *chip
)
अणु
    वापस ((NV_RD32(&chip->Rop->FअगरoFree, 0) < chip->FअगरoEmptyCount) ||
	    NV_RD32(&chip->PGRAPH[0x000006B0/4], 0) & 0x01);
पूर्ण
अटल पूर्णांक nv4Busy
(
    RIVA_HW_INST *chip
)
अणु
    वापस ((NV_RD32(&chip->Rop->FअगरoFree, 0) < chip->FअगरoEmptyCount) ||
	    NV_RD32(&chip->PGRAPH[0x00000700/4], 0) & 0x01);
पूर्ण
अटल पूर्णांक nv10Busy
(
    RIVA_HW_INST *chip
)
अणु
    वापस ((NV_RD32(&chip->Rop->FअगरoFree, 0) < chip->FअगरoEmptyCount) ||
	    NV_RD32(&chip->PGRAPH[0x00000700/4], 0) & 0x01);
पूर्ण

अटल व्योम vgaLockUnlock
(
    RIVA_HW_INST *chip,
    पूर्णांक           Lock
)
अणु
    U008 cr11;
    VGA_WR08(chip->PCIO, 0x3D4, 0x11);
    cr11 = VGA_RD08(chip->PCIO, 0x3D5);
    अगर(Lock) cr11 |= 0x80;
    अन्यथा cr11 &= ~0x80;
    VGA_WR08(chip->PCIO, 0x3D5, cr11);
पूर्ण
अटल व्योम nv3LockUnlock
(
    RIVA_HW_INST *chip,
    पूर्णांक           Lock
)
अणु
    VGA_WR08(chip->PVIO, 0x3C4, 0x06);
    VGA_WR08(chip->PVIO, 0x3C5, Lock ? 0x99 : 0x57);
    vgaLockUnlock(chip, Lock);
पूर्ण
अटल व्योम nv4LockUnlock
(
    RIVA_HW_INST *chip,
    पूर्णांक           Lock
)
अणु
    VGA_WR08(chip->PCIO, 0x3D4, 0x1F);
    VGA_WR08(chip->PCIO, 0x3D5, Lock ? 0x99 : 0x57);
    vgaLockUnlock(chip, Lock);
पूर्ण

अटल पूर्णांक ShowHideCursor
(
    RIVA_HW_INST *chip,
    पूर्णांक           ShowHide
)
अणु
    पूर्णांक cursor;
    cursor                      =  chip->CurrentState->cursor1;
    chip->CurrentState->cursor1 = (chip->CurrentState->cursor1 & 0xFE) |
                                  (ShowHide & 0x01);
    VGA_WR08(chip->PCIO, 0x3D4, 0x31);
    VGA_WR08(chip->PCIO, 0x3D5, chip->CurrentState->cursor1);
    वापस (cursor & 0x01);
पूर्ण

/****************************************************************************\
*                                                                            *
* The video arbitration routines calculate some "magic" numbers.  Fixes      *
* the snow seen when accessing the framebuffer without it.                   *
* It just works (I hope).                                                    *
*                                                                            *
\****************************************************************************/

#घोषणा DEFAULT_GR_LWM 100
#घोषणा DEFAULT_VID_LWM 100
#घोषणा DEFAULT_GR_BURST_SIZE 256
#घोषणा DEFAULT_VID_BURST_SIZE 128
#घोषणा VIDEO		0
#घोषणा GRAPHICS	1
#घोषणा MPORT		2
#घोषणा ENGINE		3
#घोषणा GFIFO_SIZE	320
#घोषणा GFIFO_SIZE_128	256
#घोषणा MFIFO_SIZE	120
#घोषणा VFIFO_SIZE	256

प्रकार काष्ठा अणु
  पूर्णांक gdrain_rate;
  पूर्णांक vdrain_rate;
  पूर्णांक mdrain_rate;
  पूर्णांक gburst_size;
  पूर्णांक vburst_size;
  अक्षर vid_en;
  अक्षर gr_en;
  पूर्णांक wcmocc, wcgocc, wcvocc, wcvlwm, wcglwm;
  पूर्णांक by_gfacc;
  अक्षर vid_only_once;
  अक्षर gr_only_once;
  अक्षर first_vacc;
  अक्षर first_gacc;
  अक्षर first_macc;
  पूर्णांक vocc;
  पूर्णांक gocc;
  पूर्णांक mocc;
  अक्षर cur;
  अक्षर engine_en;
  अक्षर converged;
  पूर्णांक priority;
पूर्ण nv3_arb_info;
प्रकार काष्ठा अणु
  पूर्णांक graphics_lwm;
  पूर्णांक video_lwm;
  पूर्णांक graphics_burst_size;
  पूर्णांक video_burst_size;
  पूर्णांक graphics_hi_priority;
  पूर्णांक media_hi_priority;
  पूर्णांक rtl_values;
  पूर्णांक valid;
पूर्ण nv3_fअगरo_info;
प्रकार काष्ठा अणु
  अक्षर pix_bpp;
  अक्षर enable_video;
  अक्षर gr_during_vid;
  अक्षर enable_mp;
  पूर्णांक memory_width;
  पूर्णांक video_scale;
  पूर्णांक pclk_khz;
  पूर्णांक mclk_khz;
  पूर्णांक mem_page_miss;
  पूर्णांक mem_latency;
  अक्षर mem_aligned;
पूर्ण nv3_sim_state;
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
अटल पूर्णांक nv3_iterate(nv3_fअगरo_info *res_info, nv3_sim_state * state, nv3_arb_info *ainfo)
अणु
    पूर्णांक iter = 0;
    पूर्णांक पंचांगp;
    पूर्णांक vfsize, mfsize, gfsize;
    पूर्णांक mburst_size = 32;
    पूर्णांक mmisses, gmisses, vmisses;
    पूर्णांक misses;
    पूर्णांक vlwm, glwm;
    पूर्णांक last, next, cur;
    पूर्णांक max_gfsize ;
    दीर्घ ns;

    vlwm = 0;
    glwm = 0;
    vfsize = 0;
    gfsize = 0;
    cur = ainfo->cur;
    mmisses = 2;
    gmisses = 2;
    vmisses = 2;
    अगर (ainfo->gburst_size == 128) max_gfsize = GFIFO_SIZE_128;
    अन्यथा  max_gfsize = GFIFO_SIZE;
    max_gfsize = GFIFO_SIZE;
    जबतक (1)
    अणु
        अगर (ainfo->vid_en)
        अणु
            अगर (ainfo->wcvocc > ainfo->vocc) ainfo->wcvocc = ainfo->vocc;
            अगर (ainfo->wcvlwm > vlwm) ainfo->wcvlwm = vlwm ;
            ns = 1000000 * ainfo->vburst_size/(state->memory_width/8)/state->mclk_khz;
            vfsize = ns * ainfo->vdrain_rate / 1000000;
            vfsize =  ainfo->wcvlwm - ainfo->vburst_size + vfsize;
        पूर्ण
        अगर (state->enable_mp)
        अणु
            अगर (ainfo->wcmocc > ainfo->mocc) ainfo->wcmocc = ainfo->mocc;
        पूर्ण
        अगर (ainfo->gr_en)
        अणु
            अगर (ainfo->wcglwm > glwm) ainfo->wcglwm = glwm ;
            अगर (ainfo->wcgocc > ainfo->gocc) ainfo->wcgocc = ainfo->gocc;
            ns = 1000000 * (ainfo->gburst_size/(state->memory_width/8))/state->mclk_khz;
            gfsize = (ns * (दीर्घ) ainfo->gdrain_rate)/1000000;
            gfsize = ainfo->wcglwm - ainfo->gburst_size + gfsize;
        पूर्ण
        mfsize = 0;
        अगर (!state->gr_during_vid && ainfo->vid_en)
            अगर (ainfo->vid_en && (ainfo->vocc < 0) && !ainfo->vid_only_once)
                next = VIDEO;
            अन्यथा अगर (ainfo->mocc < 0)
                next = MPORT;
            अन्यथा अगर (ainfo->gocc< ainfo->by_gfacc)
                next = GRAPHICS;
            अन्यथा वापस (0);
        अन्यथा चयन (ainfo->priority)
            अणु
                हाल VIDEO:
                    अगर (ainfo->vid_en && ainfo->vocc<0 && !ainfo->vid_only_once)
                        next = VIDEO;
                    अन्यथा अगर (ainfo->gr_en && ainfo->gocc<0 && !ainfo->gr_only_once)
                        next = GRAPHICS;
                    अन्यथा अगर (ainfo->mocc<0)
                        next = MPORT;
                    अन्यथा    वापस (0);
                    अवरोध;
                हाल GRAPHICS:
                    अगर (ainfo->gr_en && ainfo->gocc<0 && !ainfo->gr_only_once)
                        next = GRAPHICS;
                    अन्यथा अगर (ainfo->vid_en && ainfo->vocc<0 && !ainfo->vid_only_once)
                        next = VIDEO;
                    अन्यथा अगर (ainfo->mocc<0)
                        next = MPORT;
                    अन्यथा    वापस (0);
                    अवरोध;
                शेष:
                    अगर (ainfo->mocc<0)
                        next = MPORT;
                    अन्यथा अगर (ainfo->gr_en && ainfo->gocc<0 && !ainfo->gr_only_once)
                        next = GRAPHICS;
                    अन्यथा अगर (ainfo->vid_en && ainfo->vocc<0 && !ainfo->vid_only_once)
                        next = VIDEO;
                    अन्यथा    वापस (0);
                    अवरोध;
            पूर्ण
        last = cur;
        cur = next;
        iter++;
        चयन (cur)
        अणु
            हाल VIDEO:
                अगर (last==cur)    misses = 0;
                अन्यथा अगर (ainfo->first_vacc)   misses = vmisses;
                अन्यथा    misses = 1;
                ainfo->first_vacc = 0;
                अगर (last!=cur)
                अणु
                    ns =  1000000 * (vmisses*state->mem_page_miss + state->mem_latency)/state->mclk_khz; 
                    vlwm = ns * ainfo->vdrain_rate/ 1000000;
                    vlwm = ainfo->vocc - vlwm;
                पूर्ण
                ns = 1000000*(misses*state->mem_page_miss + ainfo->vburst_size)/(state->memory_width/8)/state->mclk_khz;
                ainfo->vocc = ainfo->vocc + ainfo->vburst_size - ns*ainfo->vdrain_rate/1000000;
                ainfo->gocc = ainfo->gocc - ns*ainfo->gdrain_rate/1000000;
                ainfo->mocc = ainfo->mocc - ns*ainfo->mdrain_rate/1000000;
                अवरोध;
            हाल GRAPHICS:
                अगर (last==cur)    misses = 0;
                अन्यथा अगर (ainfo->first_gacc)   misses = gmisses;
                अन्यथा    misses = 1;
                ainfo->first_gacc = 0;
                अगर (last!=cur)
                अणु
                    ns = 1000000*(gmisses*state->mem_page_miss + state->mem_latency)/state->mclk_khz ;
                    glwm = ns * ainfo->gdrain_rate/1000000;
                    glwm = ainfo->gocc - glwm;
                पूर्ण
                ns = 1000000*(misses*state->mem_page_miss + ainfo->gburst_size/(state->memory_width/8))/state->mclk_khz;
                ainfo->vocc = ainfo->vocc + 0 - ns*ainfo->vdrain_rate/1000000;
                ainfo->gocc = ainfo->gocc + ainfo->gburst_size - ns*ainfo->gdrain_rate/1000000;
                ainfo->mocc = ainfo->mocc + 0 - ns*ainfo->mdrain_rate/1000000;
                अवरोध;
            शेष:
                अगर (last==cur)    misses = 0;
                अन्यथा अगर (ainfo->first_macc)   misses = mmisses;
                अन्यथा    misses = 1;
                ainfo->first_macc = 0;
                ns = 1000000*(misses*state->mem_page_miss + mburst_size/(state->memory_width/8))/state->mclk_khz;
                ainfo->vocc = ainfo->vocc + 0 - ns*ainfo->vdrain_rate/1000000;
                ainfo->gocc = ainfo->gocc + 0 - ns*ainfo->gdrain_rate/1000000;
                ainfo->mocc = ainfo->mocc + mburst_size - ns*ainfo->mdrain_rate/1000000;
                अवरोध;
        पूर्ण
        अगर (iter>100)
        अणु
            ainfo->converged = 0;
            वापस (1);
        पूर्ण
        ns = 1000000*ainfo->gburst_size/(state->memory_width/8)/state->mclk_khz;
        पंचांगp = ns * ainfo->gdrain_rate/1000000;
        अगर (असल(ainfo->gburst_size) + ((असल(ainfo->wcglwm) + 16 ) & ~0x7) - पंचांगp > max_gfsize)
        अणु
            ainfo->converged = 0;
            वापस (1);
        पूर्ण
        ns = 1000000*ainfo->vburst_size/(state->memory_width/8)/state->mclk_khz;
        पंचांगp = ns * ainfo->vdrain_rate/1000000;
        अगर (असल(ainfo->vburst_size) + (असल(ainfo->wcvlwm + 32) & ~0xf)  - पंचांगp> VFIFO_SIZE)
        अणु
            ainfo->converged = 0;
            वापस (1);
        पूर्ण
        अगर (असल(ainfo->gocc) > max_gfsize)
        अणु
            ainfo->converged = 0;
            वापस (1);
        पूर्ण
        अगर (असल(ainfo->vocc) > VFIFO_SIZE)
        अणु
            ainfo->converged = 0;
            वापस (1);
        पूर्ण
        अगर (असल(ainfo->mocc) > MFIFO_SIZE)
        अणु
            ainfo->converged = 0;
            वापस (1);
        पूर्ण
        अगर (असल(vfsize) > VFIFO_SIZE)
        अणु
            ainfo->converged = 0;
            वापस (1);
        पूर्ण
        अगर (असल(gfsize) > max_gfsize)
        अणु
            ainfo->converged = 0;
            वापस (1);
        पूर्ण
        अगर (असल(mfsize) > MFIFO_SIZE)
        अणु
            ainfo->converged = 0;
            वापस (1);
        पूर्ण
    पूर्ण
पूर्ण
अटल अक्षर nv3_arb(nv3_fअगरo_info * res_info, nv3_sim_state * state,  nv3_arb_info *ainfo) 
अणु
    दीर्घ ens, vns, mns, gns;
    पूर्णांक mmisses, gmisses, vmisses, eburst_size, mburst_size;
    पूर्णांक refresh_cycle;

    refresh_cycle = 2*(state->mclk_khz/state->pclk_khz) + 5;
    mmisses = 2;
    अगर (state->mem_aligned) gmisses = 2;
    अन्यथा    gmisses = 3;
    vmisses = 2;
    eburst_size = state->memory_width * 1;
    mburst_size = 32;
    gns = 1000000 * (gmisses*state->mem_page_miss + state->mem_latency)/state->mclk_khz;
    ainfo->by_gfacc = gns*ainfo->gdrain_rate/1000000;
    ainfo->wcmocc = 0;
    ainfo->wcgocc = 0;
    ainfo->wcvocc = 0;
    ainfo->wcvlwm = 0;
    ainfo->wcglwm = 0;
    ainfo->engine_en = 1;
    ainfo->converged = 1;
    अगर (ainfo->engine_en)
    अणु
        ens =  1000000*(state->mem_page_miss + eburst_size/(state->memory_width/8) +refresh_cycle)/state->mclk_khz;
        ainfo->mocc = state->enable_mp ? 0-ens*ainfo->mdrain_rate/1000000 : 0;
        ainfo->vocc = ainfo->vid_en ? 0-ens*ainfo->vdrain_rate/1000000 : 0;
        ainfo->gocc = ainfo->gr_en ? 0-ens*ainfo->gdrain_rate/1000000 : 0;
        ainfo->cur = ENGINE;
        ainfo->first_vacc = 1;
        ainfo->first_gacc = 1;
        ainfo->first_macc = 1;
        nv3_iterate(res_info, state,ainfo);
    पूर्ण
    अगर (state->enable_mp)
    अणु
        mns = 1000000 * (mmisses*state->mem_page_miss + mburst_size/(state->memory_width/8) + refresh_cycle)/state->mclk_khz;
        ainfo->mocc = state->enable_mp ? 0 : mburst_size - mns*ainfo->mdrain_rate/1000000;
        ainfo->vocc = ainfo->vid_en ? 0 : 0- mns*ainfo->vdrain_rate/1000000;
        ainfo->gocc = ainfo->gr_en ? 0: 0- mns*ainfo->gdrain_rate/1000000;
        ainfo->cur = MPORT;
        ainfo->first_vacc = 1;
        ainfo->first_gacc = 1;
        ainfo->first_macc = 0;
        nv3_iterate(res_info, state,ainfo);
    पूर्ण
    अगर (ainfo->gr_en)
    अणु
        ainfo->first_vacc = 1;
        ainfo->first_gacc = 0;
        ainfo->first_macc = 1;
        gns = 1000000*(gmisses*state->mem_page_miss + ainfo->gburst_size/(state->memory_width/8) + refresh_cycle)/state->mclk_khz;
        ainfo->gocc = ainfo->gburst_size - gns*ainfo->gdrain_rate/1000000;
        ainfo->vocc = ainfo->vid_en? 0-gns*ainfo->vdrain_rate/1000000 : 0;
        ainfo->mocc = state->enable_mp ?  0-gns*ainfo->mdrain_rate/1000000: 0;
        ainfo->cur = GRAPHICS;
        nv3_iterate(res_info, state,ainfo);
    पूर्ण
    अगर (ainfo->vid_en)
    अणु
        ainfo->first_vacc = 0;
        ainfo->first_gacc = 1;
        ainfo->first_macc = 1;
        vns = 1000000*(vmisses*state->mem_page_miss + ainfo->vburst_size/(state->memory_width/8) + refresh_cycle)/state->mclk_khz;
        ainfo->vocc = ainfo->vburst_size - vns*ainfo->vdrain_rate/1000000;
        ainfo->gocc = ainfo->gr_en? (0-vns*ainfo->gdrain_rate/1000000) : 0;
        ainfo->mocc = state->enable_mp? 0-vns*ainfo->mdrain_rate/1000000 :0 ;
        ainfo->cur = VIDEO;
        nv3_iterate(res_info, state, ainfo);
    पूर्ण
    अगर (ainfo->converged)
    अणु
        res_info->graphics_lwm = (पूर्णांक)असल(ainfo->wcglwm) + 16;
        res_info->video_lwm = (पूर्णांक)असल(ainfo->wcvlwm) + 32;
        res_info->graphics_burst_size = ainfo->gburst_size;
        res_info->video_burst_size = ainfo->vburst_size;
        res_info->graphics_hi_priority = (ainfo->priority == GRAPHICS);
        res_info->media_hi_priority = (ainfo->priority == MPORT);
        अगर (res_info->video_lwm > 160)
        अणु
            res_info->graphics_lwm = 256;
            res_info->video_lwm = 128;
            res_info->graphics_burst_size = 64;
            res_info->video_burst_size = 64;
            res_info->graphics_hi_priority = 0;
            res_info->media_hi_priority = 0;
            ainfo->converged = 0;
            वापस (0);
        पूर्ण
        अगर (res_info->video_lwm > 128)
        अणु
            res_info->video_lwm = 128;
        पूर्ण
        वापस (1);
    पूर्ण
    अन्यथा
    अणु
        res_info->graphics_lwm = 256;
        res_info->video_lwm = 128;
        res_info->graphics_burst_size = 64;
        res_info->video_burst_size = 64;
        res_info->graphics_hi_priority = 0;
        res_info->media_hi_priority = 0;
        वापस (0);
    पूर्ण
पूर्ण
अटल अक्षर nv3_get_param(nv3_fअगरo_info *res_info, nv3_sim_state * state, nv3_arb_info *ainfo)
अणु
    पूर्णांक करोne, g,v, p;
    
    करोne = 0;
    क्रम (p=0; p < 2; p++)
    अणु
        क्रम (g=128 ; g > 32; g= g>> 1)
        अणु
            क्रम (v=128; v >=32; v = v>> 1)
            अणु
                ainfo->priority = p;
                ainfo->gburst_size = g;     
                ainfo->vburst_size = v;
                करोne = nv3_arb(res_info, state,ainfo);
                अगर (करोne && (g==128))
                    अगर ((res_info->graphics_lwm + g) > 256)
                        करोne = 0;
                अगर (करोne)
                    जाओ Done;
            पूर्ण
        पूर्ण
    पूर्ण

 Done:
    वापस करोne;
पूर्ण
अटल व्योम nv3CalcArbitration 
(
    nv3_fअगरo_info * res_info,
    nv3_sim_state * state
)
अणु
    nv3_fअगरo_info save_info;
    nv3_arb_info ainfo;
    अक्षर   res_gr, res_vid;

    ainfo.gr_en = 1;
    ainfo.vid_en = state->enable_video;
    ainfo.vid_only_once = 0;
    ainfo.gr_only_once = 0;
    ainfo.gdrain_rate = (पूर्णांक) state->pclk_khz * (state->pix_bpp/8);
    ainfo.vdrain_rate = (पूर्णांक) state->pclk_khz * 2;
    अगर (state->video_scale != 0)
        ainfo.vdrain_rate = ainfo.vdrain_rate/state->video_scale;
    ainfo.mdrain_rate = 33000;
    res_info->rtl_values = 0;
    अगर (!state->gr_during_vid && state->enable_video)
    अणु
        ainfo.gr_only_once = 1;
        ainfo.gr_en = 1;
        ainfo.gdrain_rate = 0;
        res_vid = nv3_get_param(res_info, state,  &ainfo);
        res_vid = ainfo.converged;
        save_info.video_lwm = res_info->video_lwm;
        save_info.video_burst_size = res_info->video_burst_size;
        ainfo.vid_en = 1;
        ainfo.vid_only_once = 1;
        ainfo.gr_en = 1;
        ainfo.gdrain_rate = (पूर्णांक) state->pclk_khz * (state->pix_bpp/8);
        ainfo.vdrain_rate = 0;
        res_gr = nv3_get_param(res_info, state,  &ainfo);
        res_gr = ainfo.converged;
        res_info->video_lwm = save_info.video_lwm;
        res_info->video_burst_size = save_info.video_burst_size;
        res_info->valid = res_gr & res_vid;
    पूर्ण
    अन्यथा
    अणु
        अगर (!ainfo.gr_en) ainfo.gdrain_rate = 0;
        अगर (!ainfo.vid_en) ainfo.vdrain_rate = 0;
        res_gr = nv3_get_param(res_info, state,  &ainfo);
        res_info->valid = ainfo.converged;
    पूर्ण
पूर्ण
अटल व्योम nv3UpdateArbitrationSettings
(
    अचिन्हित      VClk, 
    अचिन्हित      pixelDepth, 
    अचिन्हित     *burst,
    अचिन्हित     *lwm,
    RIVA_HW_INST *chip
)
अणु
    nv3_fअगरo_info fअगरo_data;
    nv3_sim_state sim_data;
    अचिन्हित पूर्णांक M, N, P, pll, MClk;
    
    pll = NV_RD32(&chip->PRAMDAC0[0x00000504/4], 0);
    M = (pll >> 0) & 0xFF; N = (pll >> 8) & 0xFF; P = (pll >> 16) & 0x0F;
    MClk = (N * chip->CrystalFreqKHz / M) >> P;
    sim_data.pix_bpp        = (अक्षर)pixelDepth;
    sim_data.enable_video   = 0;
    sim_data.enable_mp      = 0;
    sim_data.video_scale    = 1;
    sim_data.memory_width   = (NV_RD32(&chip->PEXTDEV[0x00000000/4], 0) & 0x10) ?
	128 : 64;
    sim_data.memory_width   = 128;

    sim_data.mem_latency    = 9;
    sim_data.mem_aligned    = 1;
    sim_data.mem_page_miss  = 11;
    sim_data.gr_during_vid  = 0;
    sim_data.pclk_khz       = VClk;
    sim_data.mclk_khz       = MClk;
    nv3CalcArbitration(&fअगरo_data, &sim_data);
    अगर (fअगरo_data.valid)
    अणु
        पूर्णांक  b = fअगरo_data.graphics_burst_size >> 4;
        *burst = 0;
        जबतक (b >>= 1)
	    (*burst)++;
        *lwm   = fअगरo_data.graphics_lwm >> 3;
    पूर्ण
    अन्यथा
    अणु
        *lwm   = 0x24;
        *burst = 0x2;
    पूर्ण
पूर्ण
अटल व्योम nv4CalcArbitration 
(
    nv4_fअगरo_info *fअगरo,
    nv4_sim_state *arb
)
अणु
    पूर्णांक data, pagemiss, cas,width, video_enable, bpp;
    पूर्णांक nvclks, mclks, pclks, vpagemiss, crtpagemiss, vbs;
    पूर्णांक found, mclk_extra, mclk_loop, cbs, m1, p1;
    पूर्णांक mclk_freq, pclk_freq, nvclk_freq, mp_enable;
    पूर्णांक us_m, us_n, us_p, video_drain_rate, crtc_drain_rate;
    पूर्णांक vpm_us, us_video, vlwm, video_fill_us, cpm_us, us_crt,clwm;

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
        mclks+=4;
    nvclks += 0;
    pclks += 0;
    found = 0;
    vbs = 0;
    जबतक (found != 1)
    अणु
        fअगरo->valid = 1;
        found = 1;
        mclk_loop = mclks+mclk_extra;
        us_m = mclk_loop *1000*1000 / mclk_freq;
        us_n = nvclks*1000*1000 / nvclk_freq;
        us_p = nvclks*1000*1000 / pclk_freq;
        अगर (video_enable)
        अणु
            video_drain_rate = pclk_freq * 2;
            crtc_drain_rate = pclk_freq * bpp/8;
            vpagemiss = 2;
            vpagemiss += 1;
            crtpagemiss = 2;
            vpm_us = (vpagemiss * pagemiss)*1000*1000/mclk_freq;
            अगर (nvclk_freq * 2 > mclk_freq * width)
                video_fill_us = cbs*1000*1000 / 16 / nvclk_freq ;
            अन्यथा
                video_fill_us = cbs*1000*1000 / (8 * width) / mclk_freq;
            us_video = vpm_us + us_m + us_n + us_p + video_fill_us;
            vlwm = us_video * video_drain_rate/(1000*1000);
            vlwm++;
            vbs = 128;
            अगर (vlwm > 128) vbs = 64;
            अगर (vlwm > (256-64)) vbs = 32;
            अगर (nvclk_freq * 2 > mclk_freq * width)
                video_fill_us = vbs *1000*1000/ 16 / nvclk_freq ;
            अन्यथा
                video_fill_us = vbs*1000*1000 / (8 * width) / mclk_freq;
            cpm_us = crtpagemiss  * pagemiss *1000*1000/ mclk_freq;
            us_crt =
            us_video
            +video_fill_us
            +cpm_us
            +us_m + us_n +us_p
            ;
            clwm = us_crt * crtc_drain_rate/(1000*1000);
            clwm++;
        पूर्ण
        अन्यथा
        अणु
            crtc_drain_rate = pclk_freq * bpp/8;
            crtpagemiss = 2;
            crtpagemiss += 1;
            cpm_us = crtpagemiss  * pagemiss *1000*1000/ mclk_freq;
            us_crt =  cpm_us + us_m + us_n + us_p ;
            clwm = us_crt * crtc_drain_rate/(1000*1000);
            clwm++;
        पूर्ण
        m1 = clwm + cbs - 512;
        p1 = m1 * pclk_freq / mclk_freq;
        p1 = p1 * bpp / 8;
        अगर ((p1 < m1) && (m1 > 0))
        अणु
            fअगरo->valid = 0;
            found = 0;
            अगर (mclk_extra ==0)   found = 1;
            mclk_extra--;
        पूर्ण
        अन्यथा अगर (video_enable)
        अणु
            अगर ((clwm > 511) || (vlwm > 255))
            अणु
                fअगरo->valid = 0;
                found = 0;
                अगर (mclk_extra ==0)   found = 1;
                mclk_extra--;
            पूर्ण
        पूर्ण
        अन्यथा
        अणु
            अगर (clwm > 519)
            अणु
                fअगरo->valid = 0;
                found = 0;
                अगर (mclk_extra ==0)   found = 1;
                mclk_extra--;
            पूर्ण
        पूर्ण
        अगर (clwm < 384) clwm = 384;
        अगर (vlwm < 128) vlwm = 128;
        data = (पूर्णांक)(clwm);
        fअगरo->graphics_lwm = data;
        fअगरo->graphics_burst_size = 128;
        data = (पूर्णांक)((vlwm+15));
        fअगरo->video_lwm = data;
        fअगरo->video_burst_size = vbs;
    पूर्ण
पूर्ण
अटल व्योम nv4UpdateArbitrationSettings
(
    अचिन्हित      VClk, 
    अचिन्हित      pixelDepth, 
    अचिन्हित     *burst,
    अचिन्हित     *lwm,
    RIVA_HW_INST *chip
)
अणु
    nv4_fअगरo_info fअगरo_data;
    nv4_sim_state sim_data;
    अचिन्हित पूर्णांक M, N, P, pll, MClk, NVClk, cfg1;

    pll = NV_RD32(&chip->PRAMDAC0[0x00000504/4], 0);
    M = (pll >> 0)  & 0xFF; N = (pll >> 8)  & 0xFF; P = (pll >> 16) & 0x0F;
    MClk  = (N * chip->CrystalFreqKHz / M) >> P;
    pll = NV_RD32(&chip->PRAMDAC0[0x00000500/4], 0);
    M = (pll >> 0)  & 0xFF; N = (pll >> 8)  & 0xFF; P = (pll >> 16) & 0x0F;
    NVClk  = (N * chip->CrystalFreqKHz / M) >> P;
    cfg1 = NV_RD32(&chip->PFB[0x00000204/4], 0);
    sim_data.pix_bpp        = (अक्षर)pixelDepth;
    sim_data.enable_video   = 0;
    sim_data.enable_mp      = 0;
    sim_data.memory_width   = (NV_RD32(&chip->PEXTDEV[0x00000000/4], 0) & 0x10) ?
	128 : 64;
    sim_data.mem_latency    = (अक्षर)cfg1 & 0x0F;
    sim_data.mem_aligned    = 1;
    sim_data.mem_page_miss  = (अक्षर)(((cfg1 >> 4) &0x0F) + ((cfg1 >> 31) & 0x01));
    sim_data.gr_during_vid  = 0;
    sim_data.pclk_khz       = VClk;
    sim_data.mclk_khz       = MClk;
    sim_data.nvclk_khz      = NVClk;
    nv4CalcArbitration(&fअगरo_data, &sim_data);
    अगर (fअगरo_data.valid)
    अणु
        पूर्णांक  b = fअगरo_data.graphics_burst_size >> 4;
        *burst = 0;
        जबतक (b >>= 1)
	    (*burst)++;
        *lwm   = fअगरo_data.graphics_lwm >> 3;
    पूर्ण
पूर्ण
अटल व्योम nv10CalcArbitration 
(
    nv10_fअगरo_info *fअगरo,
    nv10_sim_state *arb
)
अणु
    पूर्णांक data, pagemiss, width, video_enable, bpp;
    पूर्णांक nvclks, mclks, pclks, vpagemiss, crtpagemiss;
    पूर्णांक nvclk_fill;
    पूर्णांक found, mclk_extra, mclk_loop, cbs, m1;
    पूर्णांक mclk_freq, pclk_freq, nvclk_freq, mp_enable;
    पूर्णांक us_m, us_m_min, us_n, us_p, crtc_drain_rate;
    पूर्णांक vus_m;
    पूर्णांक vpm_us, us_video, cpm_us, us_crt,clwm;
    पूर्णांक clwm_rnd_करोwn;
    पूर्णांक m2us, us_pipe_min, p1clk, p2;
    पूर्णांक min_mclk_extra;
    पूर्णांक us_min_mclk_extra;

    fअगरo->valid = 1;
    pclk_freq = arb->pclk_khz; /* freq in KHz */
    mclk_freq = arb->mclk_khz;
    nvclk_freq = arb->nvclk_khz;
    pagemiss = arb->mem_page_miss;
    width = arb->memory_width/64;
    video_enable = arb->enable_video;
    bpp = arb->pix_bpp;
    mp_enable = arb->enable_mp;
    clwm = 0;

    cbs = 512;

    pclks = 4; /* lwm detect. */

    nvclks = 3; /* lwm -> sync. */
    nvclks += 2; /* fbi bus cycles (1 req + 1 busy) */

    mclks  = 1;   /* 2 edge sync.  may be very बंद to edge so just put one. */

    mclks += 1;   /* arb_hp_req */
    mclks += 5;   /* ap_hp_req   tiling pipeline */

    mclks += 2;    /* tc_req     latency fअगरo */
    mclks += 2;    /* fb_cas_n_  memory request to fbio block */
    mclks += 7;    /* sm_d_rdv   data वापसed from fbio block */

    /* fb.rd.d.Put_gc   need to accumulate 256 bits क्रम पढ़ो */
    अगर (arb->memory_type == 0)
      अगर (arb->memory_width == 64) /* 64 bit bus */
        mclks += 4;
      अन्यथा
        mclks += 2;
    अन्यथा
      अगर (arb->memory_width == 64) /* 64 bit bus */
        mclks += 2;
      अन्यथा
        mclks += 1;

    अगर ((!video_enable) && (arb->memory_width == 128))
    अणु  
      mclk_extra = (bpp == 32) ? 31 : 42; /* Margin of error */
      min_mclk_extra = 17;
    पूर्ण
    अन्यथा
    अणु
      mclk_extra = (bpp == 32) ? 8 : 4; /* Margin of error */
      /* mclk_extra = 4; */ /* Margin of error */
      min_mclk_extra = 18;
    पूर्ण

    nvclks += 1; /* 2 edge sync.  may be very बंद to edge so just put one. */
    nvclks += 1; /* fbi_d_rdv_n */
    nvclks += 1; /* Fbi_d_rdata */
    nvclks += 1; /* crtfअगरo load */

    अगर(mp_enable)
      mclks+=4; /* Mp can get in with a burst of 8. */
    /* Extra घड़ीs determined by heuristics */

    nvclks += 0;
    pclks += 0;
    found = 0;
    जबतक(found != 1) अणु
      fअगरo->valid = 1;
      found = 1;
      mclk_loop = mclks+mclk_extra;
      us_m = mclk_loop *1000*1000 / mclk_freq; /* Mclk latency in us */
      us_m_min = mclks * 1000*1000 / mclk_freq; /* Minimum Mclk latency in us */
      us_min_mclk_extra = min_mclk_extra *1000*1000 / mclk_freq;
      us_n = nvclks*1000*1000 / nvclk_freq;/* nvclk latency in us */
      us_p = pclks*1000*1000 / pclk_freq;/* nvclk latency in us */
      us_pipe_min = us_m_min + us_n + us_p;

      vus_m = mclk_loop *1000*1000 / mclk_freq; /* Mclk latency in us */

      अगर(video_enable) अणु
        crtc_drain_rate = pclk_freq * bpp/8; /* MB/s */

        vpagemiss = 1; /* self generating page miss */
        vpagemiss += 1; /* One higher priority beक्रमe */

        crtpagemiss = 2; /* self generating page miss */
        अगर(mp_enable)
            crtpagemiss += 1; /* अगर MA0 conflict */

        vpm_us = (vpagemiss * pagemiss)*1000*1000/mclk_freq;

        us_video = vpm_us + vus_m; /* Video has separate पढ़ो वापस path */

        cpm_us = crtpagemiss  * pagemiss *1000*1000/ mclk_freq;
        us_crt =
          us_video  /* Wait क्रम video */
          +cpm_us /* CRT Page miss */
          +us_m + us_n +us_p /* other latency */
          ;

        clwm = us_crt * crtc_drain_rate/(1000*1000);
        clwm++; /* fixed poपूर्णांक <= भग्न_poपूर्णांक - 1.  Fixes that */
      पूर्ण अन्यथा अणु
        crtc_drain_rate = pclk_freq * bpp/8; /* bpp * pclk/8 */

        crtpagemiss = 1; /* self generating page miss */
        crtpagemiss += 1; /* MA0 page miss */
        अगर(mp_enable)
            crtpagemiss += 1; /* अगर MA0 conflict */
        cpm_us = crtpagemiss  * pagemiss *1000*1000/ mclk_freq;
        us_crt =  cpm_us + us_m + us_n + us_p ;
        clwm = us_crt * crtc_drain_rate/(1000*1000);
        clwm++; /* fixed poपूर्णांक <= भग्न_poपूर्णांक - 1.  Fixes that */

  /*
          //
          // Another concern, only क्रम high pclks so करोn't करो this
          // with video:
          // What happens अगर the latency to fetch the cbs is so large that
          // fअगरo empties.  In that हाल we need to have an alternate clwm value
          // based off the total burst fetch
          //
          us_crt = (cbs * 1000 * 1000)/ (8*width)/mclk_freq ;
          us_crt = us_crt + us_m + us_n + us_p + (4 * 1000 * 1000)/mclk_freq;
          clwm_mt = us_crt * crtc_drain_rate/(1000*1000);
          clwm_mt ++;
          अगर(clwm_mt > clwm)
              clwm = clwm_mt;
  */
          /* Finally, a heuristic check when width == 64 bits */
          अगर(width == 1)अणु
              nvclk_fill = nvclk_freq * 8;
              अगर(crtc_drain_rate * 100 >= nvclk_fill * 102)
                      clwm = 0xfff; /*Large number to fail */

              अन्यथा अगर(crtc_drain_rate * 100  >= nvclk_fill * 98) अणु
                  clwm = 1024;
                  cbs = 512;
              पूर्ण
          पूर्ण
      पूर्ण


      /*
        Overfill check:

        */

      clwm_rnd_करोwn = ((पूर्णांक)clwm/8)*8;
      अगर (clwm_rnd_करोwn < clwm)
          clwm += 8;

      m1 = clwm + cbs -  1024; /* Amount of overfill */
      m2us = us_pipe_min + us_min_mclk_extra;

      /* pclk cycles to drain */
      p1clk = m2us * pclk_freq/(1000*1000); 
      p2 = p1clk * bpp / 8; /* bytes drained. */

      अगर((p2 < m1) && (m1 > 0)) अणु
          fअगरo->valid = 0;
          found = 0;
          अगर(min_mclk_extra == 0)   अणु
            अगर(cbs <= 32) अणु
              found = 1; /* Can't adjust anymore! */
            पूर्ण अन्यथा अणु
              cbs = cbs/2;  /* reduce the burst size */
            पूर्ण
          पूर्ण अन्यथा अणु
            min_mclk_extra--;
          पूर्ण
      पूर्ण अन्यथा अणु
        अगर (clwm > 1023)अणु /* Have some margin */
          fअगरo->valid = 0;
          found = 0;
          अगर(min_mclk_extra == 0)   
              found = 1; /* Can't adjust anymore! */
          अन्यथा 
              min_mclk_extra--;
        पूर्ण
      पूर्ण

      अगर(clwm < (1024-cbs+8)) clwm = 1024-cbs+8;
      data = (पूर्णांक)(clwm);
      /*  म_लिखो("CRT LWM: %f bytes, prog: 0x%x, bs: 256\n", clwm, data ); */
      fअगरo->graphics_lwm = data;   fअगरo->graphics_burst_size = cbs;

      /*  म_लिखो("VID LWM: %f bytes, prog: 0x%x, bs: %d\n, ", vlwm, data, vbs ); */
      fअगरo->video_lwm = 1024;  fअगरo->video_burst_size = 512;
    पूर्ण
पूर्ण
अटल व्योम nv10UpdateArbitrationSettings
(
    अचिन्हित      VClk, 
    अचिन्हित      pixelDepth, 
    अचिन्हित     *burst,
    अचिन्हित     *lwm,
    RIVA_HW_INST *chip
)
अणु
    nv10_fअगरo_info fअगरo_data;
    nv10_sim_state sim_data;
    अचिन्हित पूर्णांक M, N, P, pll, MClk, NVClk, cfg1;

    pll = NV_RD32(&chip->PRAMDAC0[0x00000504/4], 0);
    M = (pll >> 0)  & 0xFF; N = (pll >> 8)  & 0xFF; P = (pll >> 16) & 0x0F;
    MClk  = (N * chip->CrystalFreqKHz / M) >> P;
    pll = NV_RD32(&chip->PRAMDAC0[0x00000500/4], 0);
    M = (pll >> 0)  & 0xFF; N = (pll >> 8)  & 0xFF; P = (pll >> 16) & 0x0F;
    NVClk  = (N * chip->CrystalFreqKHz / M) >> P;
    cfg1 = NV_RD32(&chip->PFB[0x00000204/4], 0);
    sim_data.pix_bpp        = (अक्षर)pixelDepth;
    sim_data.enable_video   = 0;
    sim_data.enable_mp      = 0;
    sim_data.memory_type    = (NV_RD32(&chip->PFB[0x00000200/4], 0) & 0x01) ?
	1 : 0;
    sim_data.memory_width   = (NV_RD32(&chip->PEXTDEV[0x00000000/4], 0) & 0x10) ?
	128 : 64;
    sim_data.mem_latency    = (अक्षर)cfg1 & 0x0F;
    sim_data.mem_aligned    = 1;
    sim_data.mem_page_miss  = (अक्षर)(((cfg1 >> 4) &0x0F) + ((cfg1 >> 31) & 0x01));
    sim_data.gr_during_vid  = 0;
    sim_data.pclk_khz       = VClk;
    sim_data.mclk_khz       = MClk;
    sim_data.nvclk_khz      = NVClk;
    nv10CalcArbitration(&fअगरo_data, &sim_data);
    अगर (fअगरo_data.valid)
    अणु
        पूर्णांक  b = fअगरo_data.graphics_burst_size >> 4;
        *burst = 0;
        जबतक (b >>= 1)
	    (*burst)++;
        *lwm   = fअगरo_data.graphics_lwm >> 3;
    पूर्ण
पूर्ण

अटल व्योम nForceUpdateArbitrationSettings
(
    अचिन्हित      VClk,
    अचिन्हित      pixelDepth,
    अचिन्हित     *burst,
    अचिन्हित     *lwm,
    RIVA_HW_INST *chip,
    काष्ठा pci_dev *pdev
)
अणु
    nv10_fअगरo_info fअगरo_data;
    nv10_sim_state sim_data;
    अचिन्हित पूर्णांक M, N, P, pll, MClk, NVClk;
    अचिन्हित पूर्णांक uMClkPostDiv;
    काष्ठा pci_dev *dev;
    पूर्णांक करोमुख्य = pci_करोमुख्य_nr(pdev->bus);

    dev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 3);
    pci_पढ़ो_config_dword(dev, 0x6C, &uMClkPostDiv);
    pci_dev_put(dev);
    uMClkPostDiv = (uMClkPostDiv >> 8) & 0xf;

    अगर(!uMClkPostDiv) uMClkPostDiv = 4;
    MClk = 400000 / uMClkPostDiv;

    pll = NV_RD32(&chip->PRAMDAC0[0x00000500/4], 0);
    M = (pll >> 0)  & 0xFF; N = (pll >> 8)  & 0xFF; P = (pll >> 16) & 0x0F;
    NVClk  = (N * chip->CrystalFreqKHz / M) >> P;
    sim_data.pix_bpp        = (अक्षर)pixelDepth;
    sim_data.enable_video   = 0;
    sim_data.enable_mp      = 0;

    dev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 1);
    pci_पढ़ो_config_dword(dev, 0x7C, &sim_data.memory_type);
    pci_dev_put(dev);
    sim_data.memory_type    = (sim_data.memory_type >> 12) & 1;

    sim_data.memory_width   = 64;
    sim_data.mem_latency    = 3;
    sim_data.mem_aligned    = 1;
    sim_data.mem_page_miss  = 10;
    sim_data.gr_during_vid  = 0;
    sim_data.pclk_khz       = VClk;
    sim_data.mclk_khz       = MClk;
    sim_data.nvclk_khz      = NVClk;
    nv10CalcArbitration(&fअगरo_data, &sim_data);
    अगर (fअगरo_data.valid)
    अणु
        पूर्णांक  b = fअगरo_data.graphics_burst_size >> 4;
        *burst = 0;
        जबतक (b >>= 1)
	    (*burst)++;
        *lwm   = fअगरo_data.graphics_lwm >> 3;
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
अटल पूर्णांक CalcVClock
(
    पूर्णांक           घड़ीIn,
    पूर्णांक          *घड़ीOut,
    पूर्णांक          *mOut,
    पूर्णांक          *nOut,
    पूर्णांक          *pOut,
    RIVA_HW_INST *chip
)
अणु
    अचिन्हित lowM, highM, highP;
    अचिन्हित DeltaNew, DeltaOld;
    अचिन्हित VClk, Freq;
    अचिन्हित M, N, P;
    
    DeltaOld = 0xFFFFFFFF;

    VClk     = (अचिन्हित)घड़ीIn;
    
    अगर (chip->CrystalFreqKHz == 13500)
    अणु
        lowM  = 7;
        highM = 13 - (chip->Architecture == NV_ARCH_03);
    पूर्ण
    अन्यथा
    अणु
        lowM  = 8;
        highM = 14 - (chip->Architecture == NV_ARCH_03);
    पूर्ण                      

    highP = 4 - (chip->Architecture == NV_ARCH_03);
    क्रम (P = 0; P <= highP; P ++)
    अणु
        Freq = VClk << P;
        अगर ((Freq >= 128000) && (Freq <= chip->MaxVClockFreqKHz))
        अणु
            क्रम (M = lowM; M <= highM; M++)
            अणु
                N    = (VClk << P) * M / chip->CrystalFreqKHz;
                अगर(N <= 255) अणु
                Freq = (chip->CrystalFreqKHz * N / M) >> P;
                अगर (Freq > VClk)
                    DeltaNew = Freq - VClk;
                अन्यथा
                    DeltaNew = VClk - Freq;
                अगर (DeltaNew < DeltaOld)
                अणु
                    *mOut     = M;
                    *nOut     = N;
                    *pOut     = P;
                    *घड़ीOut = Freq;
                    DeltaOld  = DeltaNew;
                पूर्ण
            पूर्ण
        पूर्ण
    पूर्ण
    पूर्ण

    /* non-zero: M/N/P/घड़ी values asचिन्हित.  zero: error (not set) */
    वापस (DeltaOld != 0xFFFFFFFF);
पूर्ण
/*
 * Calculate extended mode parameters (SVGA) and save in a 
 * mode state काष्ठाure.
 */
पूर्णांक CalcStateExt
(
    RIVA_HW_INST  *chip,
    RIVA_HW_STATE *state,
    काष्ठा pci_dev *pdev,
    पूर्णांक            bpp,
    पूर्णांक            width,
    पूर्णांक            hDisplaySize,
    पूर्णांक            height,
    पूर्णांक            करोtClock
)
अणु
    पूर्णांक pixelDepth;
    पूर्णांक VClk, m, n, p;

    /*
     * Save mode parameters.
     */
    state->bpp    = bpp;    /* this is not bitsPerPixel, it's 8,15,16,32 */
    state->width  = width;
    state->height = height;
    /*
     * Extended RIVA रेजिस्टरs.
     */
    pixelDepth = (bpp + 1)/8;
    अगर (!CalcVClock(करोtClock, &VClk, &m, &n, &p, chip))
    	वापस -EINVAL;

    चयन (chip->Architecture)
    अणु
        हाल NV_ARCH_03:
            nv3UpdateArbitrationSettings(VClk, 
                                         pixelDepth * 8, 
                                        &(state->arbitration0),
                                        &(state->arbitration1),
                                         chip);
            state->cursor0  = 0x00;
            state->cursor1  = 0x78;
            state->cursor2  = 0x00000000;
            state->pllsel   = 0x10010100;
            state->config   = ((width + 31)/32)
                            | (((pixelDepth > 2) ? 3 : pixelDepth) << 8)
                            | 0x1000;
            state->general  = 0x00100100;
            state->repaपूर्णांक1 = hDisplaySize < 1280 ? 0x06 : 0x02;
            अवरोध;
        हाल NV_ARCH_04:
            nv4UpdateArbitrationSettings(VClk, 
                                         pixelDepth * 8, 
                                        &(state->arbitration0),
                                        &(state->arbitration1),
                                         chip);
            state->cursor0  = 0x00;
            state->cursor1  = 0xFC;
            state->cursor2  = 0x00000000;
            state->pllsel   = 0x10000700;
            state->config   = 0x00001114;
            state->general  = bpp == 16 ? 0x00101100 : 0x00100100;
            state->repaपूर्णांक1 = hDisplaySize < 1280 ? 0x04 : 0x00;
            अवरोध;
        हाल NV_ARCH_10:
        हाल NV_ARCH_20:
        हाल NV_ARCH_30:
            अगर((chip->Chipset == NV_CHIP_IGEFORCE2) ||
               (chip->Chipset == NV_CHIP_0x01F0))
            अणु
                nForceUpdateArbitrationSettings(VClk,
                                          pixelDepth * 8,
                                         &(state->arbitration0),
                                         &(state->arbitration1),
                                          chip, pdev);
            पूर्ण अन्यथा अणु
                nv10UpdateArbitrationSettings(VClk, 
                                          pixelDepth * 8, 
                                         &(state->arbitration0),
                                         &(state->arbitration1),
                                          chip);
            पूर्ण
            state->cursor0  = 0x80 | (chip->CursorStart >> 17);
            state->cursor1  = (chip->CursorStart >> 11) << 2;
            state->cursor2  = chip->CursorStart >> 24;
            state->pllsel   = 0x10000700;
            state->config   = NV_RD32(&chip->PFB[0x00000200/4], 0);
            state->general  = bpp == 16 ? 0x00101100 : 0x00100100;
            state->repaपूर्णांक1 = hDisplaySize < 1280 ? 0x04 : 0x00;
            अवरोध;
    पूर्ण

     /* Paul Riअक्षरds: below अगर block borks things in kernel क्रम some reason */
     /* Tony: Below is needed to set hardware in DirectColor */
    अगर((bpp != 8) && (chip->Architecture != NV_ARCH_03))
	    state->general |= 0x00000030;

    state->vpll     = (p << 16) | (n << 8) | m;
    state->repaपूर्णांक0 = (((width/8)*pixelDepth) & 0x700) >> 3;
    state->pixel    = pixelDepth > 2   ? 3    : pixelDepth;
    state->offset0  =
    state->offset1  =
    state->offset2  =
    state->offset3  = 0;
    state->pitch0   =
    state->pitch1   =
    state->pitch2   =
    state->pitch3   = pixelDepth * width;

    वापस 0;
पूर्ण
/*
 * Load fixed function state and pre-calculated/stored state.
 */
#घोषणा LOAD_FIXED_STATE(tbl,dev)                                       \
    क्रम (i = 0; i < माप(tbl##Table##dev)/8; i++)                 \
        NV_WR32(&chip->dev[tbl##Table##dev[i][0]], 0, tbl##Table##dev[i][1])
#घोषणा LOAD_FIXED_STATE_8BPP(tbl,dev)                                  \
    क्रम (i = 0; i < माप(tbl##Table##dev##_8BPP)/8; i++)            \
        NV_WR32(&chip->dev[tbl##Table##dev##_8BPP[i][0]], 0, tbl##Table##dev##_8BPP[i][1])
#घोषणा LOAD_FIXED_STATE_15BPP(tbl,dev)                                 \
    क्रम (i = 0; i < माप(tbl##Table##dev##_15BPP)/8; i++)           \
        NV_WR32(&chip->dev[tbl##Table##dev##_15BPP[i][0]], 0, tbl##Table##dev##_15BPP[i][1])
#घोषणा LOAD_FIXED_STATE_16BPP(tbl,dev)                                 \
    क्रम (i = 0; i < माप(tbl##Table##dev##_16BPP)/8; i++)           \
        NV_WR32(&chip->dev[tbl##Table##dev##_16BPP[i][0]], 0, tbl##Table##dev##_16BPP[i][1])
#घोषणा LOAD_FIXED_STATE_32BPP(tbl,dev)                                 \
    क्रम (i = 0; i < माप(tbl##Table##dev##_32BPP)/8; i++)           \
        NV_WR32(&chip->dev[tbl##Table##dev##_32BPP[i][0]], 0, tbl##Table##dev##_32BPP[i][1])

अटल व्योम UpdateFअगरoState
(
    RIVA_HW_INST  *chip
)
अणु
    पूर्णांक i;

    चयन (chip->Architecture)
    अणु
        हाल NV_ARCH_04:
            LOAD_FIXED_STATE(nv4,FIFO);
            chip->Tri03 = शून्य;
            chip->Tri05 = (RivaTexturedTriangle05 __iomem *)&(chip->FIFO[0x0000E000/4]);
            अवरोध;
        हाल NV_ARCH_10:
        हाल NV_ARCH_20:
        हाल NV_ARCH_30:
            /*
             * Initialize state क्रम the RivaTriangle3D05 routines.
             */
            LOAD_FIXED_STATE(nv10tri05,PGRAPH);
            LOAD_FIXED_STATE(nv10,FIFO);
            chip->Tri03 = शून्य;
            chip->Tri05 = (RivaTexturedTriangle05 __iomem *)&(chip->FIFO[0x0000E000/4]);
            अवरोध;
    पूर्ण
पूर्ण
अटल व्योम LoadStateExt
(
    RIVA_HW_INST  *chip,
    RIVA_HW_STATE *state
)
अणु
    पूर्णांक i;

    /*
     * Load HW fixed function state.
     */
    LOAD_FIXED_STATE(Riva,PMC);
    LOAD_FIXED_STATE(Riva,PTIMER);
    चयन (chip->Architecture)
    अणु
        हाल NV_ARCH_03:
            /*
             * Make sure frame buffer config माला_लो set beक्रमe loading PRAMIN.
             */
            NV_WR32(chip->PFB, 0x00000200, state->config);
            LOAD_FIXED_STATE(nv3,PFIFO);
            LOAD_FIXED_STATE(nv3,PRAMIN);
            LOAD_FIXED_STATE(nv3,PGRAPH);
            चयन (state->bpp)
            अणु
                हाल 15:
                हाल 16:
                    LOAD_FIXED_STATE_15BPP(nv3,PRAMIN);
                    LOAD_FIXED_STATE_15BPP(nv3,PGRAPH);
                    chip->Tri03 = (RivaTexturedTriangle03  __iomem *)&(chip->FIFO[0x0000E000/4]);
                    अवरोध;
                हाल 24:
                हाल 32:
                    LOAD_FIXED_STATE_32BPP(nv3,PRAMIN);
                    LOAD_FIXED_STATE_32BPP(nv3,PGRAPH);
                    chip->Tri03 = शून्य;
                    अवरोध;
                हाल 8:
                शेष:
                    LOAD_FIXED_STATE_8BPP(nv3,PRAMIN);
                    LOAD_FIXED_STATE_8BPP(nv3,PGRAPH);
                    chip->Tri03 = शून्य;
                    अवरोध;
            पूर्ण
            क्रम (i = 0x00000; i < 0x00800; i++)
                NV_WR32(&chip->PRAMIN[0x00000502 + i], 0, (i << 12) | 0x03);
            NV_WR32(chip->PGRAPH, 0x00000630, state->offset0);
            NV_WR32(chip->PGRAPH, 0x00000634, state->offset1);
            NV_WR32(chip->PGRAPH, 0x00000638, state->offset2);
            NV_WR32(chip->PGRAPH, 0x0000063C, state->offset3);
            NV_WR32(chip->PGRAPH, 0x00000650, state->pitch0);
            NV_WR32(chip->PGRAPH, 0x00000654, state->pitch1);
            NV_WR32(chip->PGRAPH, 0x00000658, state->pitch2);
            NV_WR32(chip->PGRAPH, 0x0000065C, state->pitch3);
            अवरोध;
        हाल NV_ARCH_04:
            /*
             * Make sure frame buffer config माला_लो set beक्रमe loading PRAMIN.
             */
            NV_WR32(chip->PFB, 0x00000200, state->config);
            LOAD_FIXED_STATE(nv4,PFIFO);
            LOAD_FIXED_STATE(nv4,PRAMIN);
            LOAD_FIXED_STATE(nv4,PGRAPH);
            चयन (state->bpp)
            अणु
                हाल 15:
                    LOAD_FIXED_STATE_15BPP(nv4,PRAMIN);
                    LOAD_FIXED_STATE_15BPP(nv4,PGRAPH);
                    chip->Tri03 = (RivaTexturedTriangle03  __iomem *)&(chip->FIFO[0x0000E000/4]);
                    अवरोध;
                हाल 16:
                    LOAD_FIXED_STATE_16BPP(nv4,PRAMIN);
                    LOAD_FIXED_STATE_16BPP(nv4,PGRAPH);
                    chip->Tri03 = (RivaTexturedTriangle03  __iomem *)&(chip->FIFO[0x0000E000/4]);
                    अवरोध;
                हाल 24:
                हाल 32:
                    LOAD_FIXED_STATE_32BPP(nv4,PRAMIN);
                    LOAD_FIXED_STATE_32BPP(nv4,PGRAPH);
                    chip->Tri03 = शून्य;
                    अवरोध;
                हाल 8:
                शेष:
                    LOAD_FIXED_STATE_8BPP(nv4,PRAMIN);
                    LOAD_FIXED_STATE_8BPP(nv4,PGRAPH);
                    chip->Tri03 = शून्य;
                    अवरोध;
            पूर्ण
            NV_WR32(chip->PGRAPH, 0x00000640, state->offset0);
            NV_WR32(chip->PGRAPH, 0x00000644, state->offset1);
            NV_WR32(chip->PGRAPH, 0x00000648, state->offset2);
            NV_WR32(chip->PGRAPH, 0x0000064C, state->offset3);
            NV_WR32(chip->PGRAPH, 0x00000670, state->pitch0);
            NV_WR32(chip->PGRAPH, 0x00000674, state->pitch1);
            NV_WR32(chip->PGRAPH, 0x00000678, state->pitch2);
            NV_WR32(chip->PGRAPH, 0x0000067C, state->pitch3);
            अवरोध;
        हाल NV_ARCH_10:
        हाल NV_ARCH_20:
        हाल NV_ARCH_30:
            अगर(chip->twoHeads) अणु
               VGA_WR08(chip->PCIO, 0x03D4, 0x44);
               VGA_WR08(chip->PCIO, 0x03D5, state->crtcOwner);
               chip->LockUnlock(chip, 0);
            पूर्ण

            LOAD_FIXED_STATE(nv10,PFIFO);
            LOAD_FIXED_STATE(nv10,PRAMIN);
            LOAD_FIXED_STATE(nv10,PGRAPH);
            चयन (state->bpp)
            अणु
                हाल 15:
                    LOAD_FIXED_STATE_15BPP(nv10,PRAMIN);
                    LOAD_FIXED_STATE_15BPP(nv10,PGRAPH);
                    chip->Tri03 = (RivaTexturedTriangle03  __iomem *)&(chip->FIFO[0x0000E000/4]);
                    अवरोध;
                हाल 16:
                    LOAD_FIXED_STATE_16BPP(nv10,PRAMIN);
                    LOAD_FIXED_STATE_16BPP(nv10,PGRAPH);
                    chip->Tri03 = (RivaTexturedTriangle03  __iomem *)&(chip->FIFO[0x0000E000/4]);
                    अवरोध;
                हाल 24:
                हाल 32:
                    LOAD_FIXED_STATE_32BPP(nv10,PRAMIN);
                    LOAD_FIXED_STATE_32BPP(nv10,PGRAPH);
                    chip->Tri03 = शून्य;
                    अवरोध;
                हाल 8:
                शेष:
                    LOAD_FIXED_STATE_8BPP(nv10,PRAMIN);
                    LOAD_FIXED_STATE_8BPP(nv10,PGRAPH);
                    chip->Tri03 = शून्य;
                    अवरोध;
            पूर्ण

            अगर(chip->Architecture == NV_ARCH_10) अणु
                NV_WR32(chip->PGRAPH, 0x00000640, state->offset0);
                NV_WR32(chip->PGRAPH, 0x00000644, state->offset1);
                NV_WR32(chip->PGRAPH, 0x00000648, state->offset2);
                NV_WR32(chip->PGRAPH, 0x0000064C, state->offset3);
                NV_WR32(chip->PGRAPH, 0x00000670, state->pitch0);
                NV_WR32(chip->PGRAPH, 0x00000674, state->pitch1);
                NV_WR32(chip->PGRAPH, 0x00000678, state->pitch2);
                NV_WR32(chip->PGRAPH, 0x0000067C, state->pitch3);
                NV_WR32(chip->PGRAPH, 0x00000680, state->pitch3);
        पूर्ण अन्यथा अणु
        NV_WR32(chip->PGRAPH, 0x00000820, state->offset0);
        NV_WR32(chip->PGRAPH, 0x00000824, state->offset1);
        NV_WR32(chip->PGRAPH, 0x00000828, state->offset2);
        NV_WR32(chip->PGRAPH, 0x0000082C, state->offset3);
        NV_WR32(chip->PGRAPH, 0x00000850, state->pitch0);
        NV_WR32(chip->PGRAPH, 0x00000854, state->pitch1);
        NV_WR32(chip->PGRAPH, 0x00000858, state->pitch2);
        NV_WR32(chip->PGRAPH, 0x0000085C, state->pitch3);
        NV_WR32(chip->PGRAPH, 0x00000860, state->pitch3);
        NV_WR32(chip->PGRAPH, 0x00000864, state->pitch3);
        NV_WR32(chip->PGRAPH, 0x000009A4, NV_RD32(chip->PFB, 0x00000200));
        NV_WR32(chip->PGRAPH, 0x000009A8, NV_RD32(chip->PFB, 0x00000204));
        पूर्ण
            अगर(chip->twoHeads) अणु
               NV_WR32(chip->PCRTC0, 0x00000860, state->head);
               NV_WR32(chip->PCRTC0, 0x00002860, state->head2);
            पूर्ण
            NV_WR32(chip->PRAMDAC, 0x00000404, NV_RD32(chip->PRAMDAC, 0x00000404) | (1 << 25));

            NV_WR32(chip->PMC, 0x00008704, 1);
            NV_WR32(chip->PMC, 0x00008140, 0);
            NV_WR32(chip->PMC, 0x00008920, 0);
            NV_WR32(chip->PMC, 0x00008924, 0);
            NV_WR32(chip->PMC, 0x00008908, 0x01ffffff);
            NV_WR32(chip->PMC, 0x0000890C, 0x01ffffff);
            NV_WR32(chip->PMC, 0x00001588, 0);

            NV_WR32(chip->PFB, 0x00000240, 0);
            NV_WR32(chip->PFB, 0x00000250, 0);
            NV_WR32(chip->PFB, 0x00000260, 0);
            NV_WR32(chip->PFB, 0x00000270, 0);
            NV_WR32(chip->PFB, 0x00000280, 0);
            NV_WR32(chip->PFB, 0x00000290, 0);
            NV_WR32(chip->PFB, 0x000002A0, 0);
            NV_WR32(chip->PFB, 0x000002B0, 0);

            NV_WR32(chip->PGRAPH, 0x00000B00, NV_RD32(chip->PFB, 0x00000240));
            NV_WR32(chip->PGRAPH, 0x00000B04, NV_RD32(chip->PFB, 0x00000244));
            NV_WR32(chip->PGRAPH, 0x00000B08, NV_RD32(chip->PFB, 0x00000248));
            NV_WR32(chip->PGRAPH, 0x00000B0C, NV_RD32(chip->PFB, 0x0000024C));
            NV_WR32(chip->PGRAPH, 0x00000B10, NV_RD32(chip->PFB, 0x00000250));
            NV_WR32(chip->PGRAPH, 0x00000B14, NV_RD32(chip->PFB, 0x00000254));
            NV_WR32(chip->PGRAPH, 0x00000B18, NV_RD32(chip->PFB, 0x00000258));
            NV_WR32(chip->PGRAPH, 0x00000B1C, NV_RD32(chip->PFB, 0x0000025C));
            NV_WR32(chip->PGRAPH, 0x00000B20, NV_RD32(chip->PFB, 0x00000260));
            NV_WR32(chip->PGRAPH, 0x00000B24, NV_RD32(chip->PFB, 0x00000264));
            NV_WR32(chip->PGRAPH, 0x00000B28, NV_RD32(chip->PFB, 0x00000268));
            NV_WR32(chip->PGRAPH, 0x00000B2C, NV_RD32(chip->PFB, 0x0000026C));
            NV_WR32(chip->PGRAPH, 0x00000B30, NV_RD32(chip->PFB, 0x00000270));
            NV_WR32(chip->PGRAPH, 0x00000B34, NV_RD32(chip->PFB, 0x00000274));
            NV_WR32(chip->PGRAPH, 0x00000B38, NV_RD32(chip->PFB, 0x00000278));
            NV_WR32(chip->PGRAPH, 0x00000B3C, NV_RD32(chip->PFB, 0x0000027C));
            NV_WR32(chip->PGRAPH, 0x00000B40, NV_RD32(chip->PFB, 0x00000280));
            NV_WR32(chip->PGRAPH, 0x00000B44, NV_RD32(chip->PFB, 0x00000284));
            NV_WR32(chip->PGRAPH, 0x00000B48, NV_RD32(chip->PFB, 0x00000288));
            NV_WR32(chip->PGRAPH, 0x00000B4C, NV_RD32(chip->PFB, 0x0000028C));
            NV_WR32(chip->PGRAPH, 0x00000B50, NV_RD32(chip->PFB, 0x00000290));
            NV_WR32(chip->PGRAPH, 0x00000B54, NV_RD32(chip->PFB, 0x00000294));
            NV_WR32(chip->PGRAPH, 0x00000B58, NV_RD32(chip->PFB, 0x00000298));
            NV_WR32(chip->PGRAPH, 0x00000B5C, NV_RD32(chip->PFB, 0x0000029C));
            NV_WR32(chip->PGRAPH, 0x00000B60, NV_RD32(chip->PFB, 0x000002A0));
            NV_WR32(chip->PGRAPH, 0x00000B64, NV_RD32(chip->PFB, 0x000002A4));
            NV_WR32(chip->PGRAPH, 0x00000B68, NV_RD32(chip->PFB, 0x000002A8));
            NV_WR32(chip->PGRAPH, 0x00000B6C, NV_RD32(chip->PFB, 0x000002AC));
            NV_WR32(chip->PGRAPH, 0x00000B70, NV_RD32(chip->PFB, 0x000002B0));
            NV_WR32(chip->PGRAPH, 0x00000B74, NV_RD32(chip->PFB, 0x000002B4));
            NV_WR32(chip->PGRAPH, 0x00000B78, NV_RD32(chip->PFB, 0x000002B8));
            NV_WR32(chip->PGRAPH, 0x00000B7C, NV_RD32(chip->PFB, 0x000002BC));
            NV_WR32(chip->PGRAPH, 0x00000F40, 0x10000000);
            NV_WR32(chip->PGRAPH, 0x00000F44, 0x00000000);
            NV_WR32(chip->PGRAPH, 0x00000F50, 0x00000040);
            NV_WR32(chip->PGRAPH, 0x00000F54, 0x00000008);
            NV_WR32(chip->PGRAPH, 0x00000F50, 0x00000200);
            क्रम (i = 0; i < (3*16); i++)
                NV_WR32(chip->PGRAPH, 0x00000F54, 0x00000000);
            NV_WR32(chip->PGRAPH, 0x00000F50, 0x00000040);
            NV_WR32(chip->PGRAPH, 0x00000F54, 0x00000000);
            NV_WR32(chip->PGRAPH, 0x00000F50, 0x00000800);
            क्रम (i = 0; i < (16*16); i++)
                NV_WR32(chip->PGRAPH, 0x00000F54, 0x00000000);
            NV_WR32(chip->PGRAPH, 0x00000F40, 0x30000000);
            NV_WR32(chip->PGRAPH, 0x00000F44, 0x00000004);
            NV_WR32(chip->PGRAPH, 0x00000F50, 0x00006400);
            क्रम (i = 0; i < (59*4); i++)
                NV_WR32(chip->PGRAPH, 0x00000F54, 0x00000000);
            NV_WR32(chip->PGRAPH, 0x00000F50, 0x00006800);
            क्रम (i = 0; i < (47*4); i++)
                NV_WR32(chip->PGRAPH, 0x00000F54, 0x00000000);
            NV_WR32(chip->PGRAPH, 0x00000F50, 0x00006C00);
            क्रम (i = 0; i < (3*4); i++)
                NV_WR32(chip->PGRAPH, 0x00000F54, 0x00000000);
            NV_WR32(chip->PGRAPH, 0x00000F50, 0x00007000);
            क्रम (i = 0; i < (19*4); i++)
                NV_WR32(chip->PGRAPH, 0x00000F54, 0x00000000);
            NV_WR32(chip->PGRAPH, 0x00000F50, 0x00007400);
            क्रम (i = 0; i < (12*4); i++)
                NV_WR32(chip->PGRAPH, 0x00000F54, 0x00000000);
            NV_WR32(chip->PGRAPH, 0x00000F50, 0x00007800);
            क्रम (i = 0; i < (12*4); i++)
                NV_WR32(chip->PGRAPH, 0x00000F54, 0x00000000);
            NV_WR32(chip->PGRAPH, 0x00000F50, 0x00004400);
            क्रम (i = 0; i < (8*4); i++)
                NV_WR32(chip->PGRAPH, 0x00000F54, 0x00000000);
            NV_WR32(chip->PGRAPH, 0x00000F50, 0x00000000);
            क्रम (i = 0; i < 16; i++)
                NV_WR32(chip->PGRAPH, 0x00000F54, 0x00000000);
            NV_WR32(chip->PGRAPH, 0x00000F50, 0x00000040);
            क्रम (i = 0; i < 4; i++)
                NV_WR32(chip->PGRAPH, 0x00000F54, 0x00000000);

            NV_WR32(chip->PCRTC, 0x00000810, state->cursorConfig);

            अगर(chip->flatPanel) अणु
               अगर((chip->Chipset & 0x0ff0) == 0x0110) अणु
                   NV_WR32(chip->PRAMDAC, 0x0528, state->dither);
               पूर्ण अन्यथा 
               अगर((chip->Chipset & 0x0ff0) >= 0x0170) अणु
                   NV_WR32(chip->PRAMDAC, 0x083C, state->dither);
               पूर्ण
            
               VGA_WR08(chip->PCIO, 0x03D4, 0x53);
               VGA_WR08(chip->PCIO, 0x03D5, 0);
               VGA_WR08(chip->PCIO, 0x03D4, 0x54);
               VGA_WR08(chip->PCIO, 0x03D5, 0);
               VGA_WR08(chip->PCIO, 0x03D4, 0x21);
               VGA_WR08(chip->PCIO, 0x03D5, 0xfa);
            पूर्ण

            VGA_WR08(chip->PCIO, 0x03D4, 0x41);
            VGA_WR08(chip->PCIO, 0x03D5, state->extra);
    पूर्ण
    LOAD_FIXED_STATE(Riva,FIFO);
    UpdateFअगरoState(chip);
    /*
     * Load HW mode state.
     */
    VGA_WR08(chip->PCIO, 0x03D4, 0x19);
    VGA_WR08(chip->PCIO, 0x03D5, state->repaपूर्णांक0);
    VGA_WR08(chip->PCIO, 0x03D4, 0x1A);
    VGA_WR08(chip->PCIO, 0x03D5, state->repaपूर्णांक1);
    VGA_WR08(chip->PCIO, 0x03D4, 0x25);
    VGA_WR08(chip->PCIO, 0x03D5, state->screen);
    VGA_WR08(chip->PCIO, 0x03D4, 0x28);
    VGA_WR08(chip->PCIO, 0x03D5, state->pixel);
    VGA_WR08(chip->PCIO, 0x03D4, 0x2D);
    VGA_WR08(chip->PCIO, 0x03D5, state->horiz);
    VGA_WR08(chip->PCIO, 0x03D4, 0x1B);
    VGA_WR08(chip->PCIO, 0x03D5, state->arbitration0);
    VGA_WR08(chip->PCIO, 0x03D4, 0x20);
    VGA_WR08(chip->PCIO, 0x03D5, state->arbitration1);
    VGA_WR08(chip->PCIO, 0x03D4, 0x30);
    VGA_WR08(chip->PCIO, 0x03D5, state->cursor0);
    VGA_WR08(chip->PCIO, 0x03D4, 0x31);
    VGA_WR08(chip->PCIO, 0x03D5, state->cursor1);
    VGA_WR08(chip->PCIO, 0x03D4, 0x2F);
    VGA_WR08(chip->PCIO, 0x03D5, state->cursor2);
    VGA_WR08(chip->PCIO, 0x03D4, 0x39);
    VGA_WR08(chip->PCIO, 0x03D5, state->पूर्णांकerlace);

    अगर(!chip->flatPanel) अणु
       NV_WR32(chip->PRAMDAC0, 0x00000508, state->vpll);
       NV_WR32(chip->PRAMDAC0, 0x0000050C, state->pllsel);
       अगर(chip->twoHeads)
          NV_WR32(chip->PRAMDAC0, 0x00000520, state->vpll2);
    पूर्ण  अन्यथा अणु
       NV_WR32(chip->PRAMDAC, 0x00000848 , state->scale);
    पूर्ण  
    NV_WR32(chip->PRAMDAC, 0x00000600 , state->general);

    /*
     * Turn off VBlank enable and reset.
     */
    NV_WR32(chip->PCRTC, 0x00000140, 0);
    NV_WR32(chip->PCRTC, 0x00000100, chip->VBlankBit);
    /*
     * Set पूर्णांकerrupt enable.
     */    
    NV_WR32(chip->PMC, 0x00000140, chip->EnableIRQ & 0x01);
    /*
     * Set current state poपूर्णांकer.
     */
    chip->CurrentState = state;
    /*
     * Reset FIFO मुक्त and empty counts.
     */
    chip->FअगरoFreeCount  = 0;
    /* Free count from first subchannel */
    chip->FअगरoEmptyCount = NV_RD32(&chip->Rop->FअगरoFree, 0);
पूर्ण
अटल व्योम UnloadStateExt
(
    RIVA_HW_INST  *chip,
    RIVA_HW_STATE *state
)
अणु
    /*
     * Save current HW state.
     */
    VGA_WR08(chip->PCIO, 0x03D4, 0x19);
    state->repaपूर्णांक0     = VGA_RD08(chip->PCIO, 0x03D5);
    VGA_WR08(chip->PCIO, 0x03D4, 0x1A);
    state->repaपूर्णांक1     = VGA_RD08(chip->PCIO, 0x03D5);
    VGA_WR08(chip->PCIO, 0x03D4, 0x25);
    state->screen       = VGA_RD08(chip->PCIO, 0x03D5);
    VGA_WR08(chip->PCIO, 0x03D4, 0x28);
    state->pixel        = VGA_RD08(chip->PCIO, 0x03D5);
    VGA_WR08(chip->PCIO, 0x03D4, 0x2D);
    state->horiz        = VGA_RD08(chip->PCIO, 0x03D5);
    VGA_WR08(chip->PCIO, 0x03D4, 0x1B);
    state->arbitration0 = VGA_RD08(chip->PCIO, 0x03D5);
    VGA_WR08(chip->PCIO, 0x03D4, 0x20);
    state->arbitration1 = VGA_RD08(chip->PCIO, 0x03D5);
    VGA_WR08(chip->PCIO, 0x03D4, 0x30);
    state->cursor0      = VGA_RD08(chip->PCIO, 0x03D5);
    VGA_WR08(chip->PCIO, 0x03D4, 0x31);
    state->cursor1      = VGA_RD08(chip->PCIO, 0x03D5);
    VGA_WR08(chip->PCIO, 0x03D4, 0x2F);
    state->cursor2      = VGA_RD08(chip->PCIO, 0x03D5);
    VGA_WR08(chip->PCIO, 0x03D4, 0x39);
    state->पूर्णांकerlace    = VGA_RD08(chip->PCIO, 0x03D5);
    state->vpll         = NV_RD32(chip->PRAMDAC0, 0x00000508);
    state->vpll2        = NV_RD32(chip->PRAMDAC0, 0x00000520);
    state->pllsel       = NV_RD32(chip->PRAMDAC0, 0x0000050C);
    state->general      = NV_RD32(chip->PRAMDAC, 0x00000600);
    state->scale        = NV_RD32(chip->PRAMDAC, 0x00000848);
    state->config       = NV_RD32(chip->PFB, 0x00000200);
    चयन (chip->Architecture)
    अणु
        हाल NV_ARCH_03:
            state->offset0  = NV_RD32(chip->PGRAPH, 0x00000630);
            state->offset1  = NV_RD32(chip->PGRAPH, 0x00000634);
            state->offset2  = NV_RD32(chip->PGRAPH, 0x00000638);
            state->offset3  = NV_RD32(chip->PGRAPH, 0x0000063C);
            state->pitch0   = NV_RD32(chip->PGRAPH, 0x00000650);
            state->pitch1   = NV_RD32(chip->PGRAPH, 0x00000654);
            state->pitch2   = NV_RD32(chip->PGRAPH, 0x00000658);
            state->pitch3   = NV_RD32(chip->PGRAPH, 0x0000065C);
            अवरोध;
        हाल NV_ARCH_04:
            state->offset0  = NV_RD32(chip->PGRAPH, 0x00000640);
            state->offset1  = NV_RD32(chip->PGRAPH, 0x00000644);
            state->offset2  = NV_RD32(chip->PGRAPH, 0x00000648);
            state->offset3  = NV_RD32(chip->PGRAPH, 0x0000064C);
            state->pitch0   = NV_RD32(chip->PGRAPH, 0x00000670);
            state->pitch1   = NV_RD32(chip->PGRAPH, 0x00000674);
            state->pitch2   = NV_RD32(chip->PGRAPH, 0x00000678);
            state->pitch3   = NV_RD32(chip->PGRAPH, 0x0000067C);
            अवरोध;
        हाल NV_ARCH_10:
        हाल NV_ARCH_20:
        हाल NV_ARCH_30:
            state->offset0  = NV_RD32(chip->PGRAPH, 0x00000640);
            state->offset1  = NV_RD32(chip->PGRAPH, 0x00000644);
            state->offset2  = NV_RD32(chip->PGRAPH, 0x00000648);
            state->offset3  = NV_RD32(chip->PGRAPH, 0x0000064C);
            state->pitch0   = NV_RD32(chip->PGRAPH, 0x00000670);
            state->pitch1   = NV_RD32(chip->PGRAPH, 0x00000674);
            state->pitch2   = NV_RD32(chip->PGRAPH, 0x00000678);
            state->pitch3   = NV_RD32(chip->PGRAPH, 0x0000067C);
            अगर(chip->twoHeads) अणु
               state->head     = NV_RD32(chip->PCRTC0, 0x00000860);
               state->head2    = NV_RD32(chip->PCRTC0, 0x00002860);
               VGA_WR08(chip->PCIO, 0x03D4, 0x44);
               state->crtcOwner = VGA_RD08(chip->PCIO, 0x03D5);
            पूर्ण
            VGA_WR08(chip->PCIO, 0x03D4, 0x41);
            state->extra = VGA_RD08(chip->PCIO, 0x03D5);
            state->cursorConfig = NV_RD32(chip->PCRTC, 0x00000810);

            अगर((chip->Chipset & 0x0ff0) == 0x0110) अणु
                state->dither = NV_RD32(chip->PRAMDAC, 0x0528);
            पूर्ण अन्यथा 
            अगर((chip->Chipset & 0x0ff0) >= 0x0170) अणु
                state->dither = NV_RD32(chip->PRAMDAC, 0x083C);
            पूर्ण
            अवरोध;
    पूर्ण
पूर्ण
अटल व्योम SetStartAddress
(
    RIVA_HW_INST *chip,
    अचिन्हित      start
)
अणु
    NV_WR32(chip->PCRTC, 0x800, start);
पूर्ण

अटल व्योम SetStartAddress3
(
    RIVA_HW_INST *chip,
    अचिन्हित      start
)
अणु
    पूर्णांक offset = start >> 2;
    पूर्णांक pan    = (start & 3) << 1;
    अचिन्हित अक्षर पंचांगp;

    /*
     * Unlock extended रेजिस्टरs.
     */
    chip->LockUnlock(chip, 0);
    /*
     * Set start address.
     */
    VGA_WR08(chip->PCIO, 0x3D4, 0x0D); VGA_WR08(chip->PCIO, 0x3D5, offset);
    offset >>= 8;
    VGA_WR08(chip->PCIO, 0x3D4, 0x0C); VGA_WR08(chip->PCIO, 0x3D5, offset);
    offset >>= 8;
    VGA_WR08(chip->PCIO, 0x3D4, 0x19); पंचांगp = VGA_RD08(chip->PCIO, 0x3D5);
    VGA_WR08(chip->PCIO, 0x3D5, (offset & 0x01F) | (पंचांगp & ~0x1F));
    VGA_WR08(chip->PCIO, 0x3D4, 0x2D); पंचांगp = VGA_RD08(chip->PCIO, 0x3D5);
    VGA_WR08(chip->PCIO, 0x3D5, (offset & 0x60) | (पंचांगp & ~0x60));
    /*
     * 4 pixel pan रेजिस्टर.
     */
    offset = VGA_RD08(chip->PCIO, chip->IO + 0x0A);
    VGA_WR08(chip->PCIO, 0x3C0, 0x13);
    VGA_WR08(chip->PCIO, 0x3C0, pan);
पूर्ण
अटल व्योम nv3SetSurfaces2D
(
    RIVA_HW_INST *chip,
    अचिन्हित     surf0,
    अचिन्हित     surf1
)
अणु
    RivaSurface __iomem *Surface =
	(RivaSurface __iomem *)&(chip->FIFO[0x0000E000/4]);

    RIVA_FIFO_FREE(*chip,Tri03,5);
    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000003);
    NV_WR32(&Surface->Offset, 0, surf0);
    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000004);
    NV_WR32(&Surface->Offset, 0, surf1);
    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000013);
पूर्ण
अटल व्योम nv4SetSurfaces2D
(
    RIVA_HW_INST *chip,
    अचिन्हित     surf0,
    अचिन्हित     surf1
)
अणु
    RivaSurface __iomem *Surface =
	(RivaSurface __iomem *)&(chip->FIFO[0x0000E000/4]);

    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000003);
    NV_WR32(&Surface->Offset, 0, surf0);
    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000004);
    NV_WR32(&Surface->Offset, 0, surf1);
    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000014);
पूर्ण
अटल व्योम nv10SetSurfaces2D
(
    RIVA_HW_INST *chip,
    अचिन्हित     surf0,
    अचिन्हित     surf1
)
अणु
    RivaSurface __iomem *Surface =
	(RivaSurface __iomem *)&(chip->FIFO[0x0000E000/4]);

    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000003);
    NV_WR32(&Surface->Offset, 0, surf0);
    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000004);
    NV_WR32(&Surface->Offset, 0, surf1);
    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000014);
पूर्ण
अटल व्योम nv3SetSurfaces3D
(
    RIVA_HW_INST *chip,
    अचिन्हित     surf0,
    अचिन्हित     surf1
)
अणु
    RivaSurface __iomem *Surface =
	(RivaSurface __iomem *)&(chip->FIFO[0x0000E000/4]);

    RIVA_FIFO_FREE(*chip,Tri03,5);
    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000005);
    NV_WR32(&Surface->Offset, 0, surf0);
    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000006);
    NV_WR32(&Surface->Offset, 0, surf1);
    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000013);
पूर्ण
अटल व्योम nv4SetSurfaces3D
(
    RIVA_HW_INST *chip,
    अचिन्हित     surf0,
    अचिन्हित     surf1
)
अणु
    RivaSurface __iomem *Surface =
	(RivaSurface __iomem *)&(chip->FIFO[0x0000E000/4]);

    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000005);
    NV_WR32(&Surface->Offset, 0, surf0);
    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000006);
    NV_WR32(&Surface->Offset, 0, surf1);
    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000014);
पूर्ण
अटल व्योम nv10SetSurfaces3D
(
    RIVA_HW_INST *chip,
    अचिन्हित     surf0,
    अचिन्हित     surf1
)
अणु
    RivaSurface3D __iomem *Surfaces3D =
	(RivaSurface3D __iomem *)&(chip->FIFO[0x0000E000/4]);

    RIVA_FIFO_FREE(*chip,Tri03,4);
    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000007);
    NV_WR32(&Surfaces3D->RenderBufferOffset, 0, surf0);
    NV_WR32(&Surfaces3D->ZBufferOffset, 0, surf1);
    NV_WR32(&chip->FIFO[0x00003800], 0, 0x80000014);
पूर्ण

/****************************************************************************\
*                                                                            *
*                      Probe RIVA Chip Configuration                         *
*                                                                            *
\****************************************************************************/

अटल व्योम nv3GetConfig
(
    RIVA_HW_INST *chip
)
अणु
    /*
     * Fill in chip configuration.
     */
    अगर (NV_RD32(&chip->PFB[0x00000000/4], 0) & 0x00000020)
    अणु
        अगर (((NV_RD32(chip->PMC, 0x00000000) & 0xF0) == 0x20)
         && ((NV_RD32(chip->PMC, 0x00000000) & 0x0F) >= 0x02))
        अणु        
            /*
             * SDRAM 128 ZX.
             */
            chip->RamBandwidthKBytesPerSec = 800000;
            चयन (NV_RD32(chip->PFB, 0x00000000) & 0x03)
            अणु
                हाल 2:
                    chip->RamAmountKBytes = 1024 * 4;
                    अवरोध;
                हाल 1:
                    chip->RamAmountKBytes = 1024 * 2;
                    अवरोध;
                शेष:
                    chip->RamAmountKBytes = 1024 * 8;
                    अवरोध;
            पूर्ण
        पूर्ण            
        अन्यथा            
        अणु
            chip->RamBandwidthKBytesPerSec = 1000000;
            chip->RamAmountKBytes          = 1024 * 8;
        पूर्ण            
    पूर्ण
    अन्यथा
    अणु
        /*
         * SGRAM 128.
         */
        chip->RamBandwidthKBytesPerSec = 1000000;
        चयन (NV_RD32(chip->PFB, 0x00000000) & 0x00000003)
        अणु
            हाल 0:
                chip->RamAmountKBytes = 1024 * 8;
                अवरोध;
            हाल 2:
                chip->RamAmountKBytes = 1024 * 4;
                अवरोध;
            शेष:
                chip->RamAmountKBytes = 1024 * 2;
                अवरोध;
        पूर्ण
    पूर्ण        
    chip->CrystalFreqKHz   = (NV_RD32(chip->PEXTDEV, 0x00000000) & 0x00000040) ? 14318 : 13500;
    chip->CURSOR           = &(chip->PRAMIN[0x00008000/4 - 0x0800/4]);
    chip->VBlankBit        = 0x00000100;
    chip->MaxVClockFreqKHz = 256000;
    /*
     * Set chip functions.
     */
    chip->Busy            = nv3Busy;
    chip->ShowHideCursor  = ShowHideCursor;
    chip->LoadStateExt    = LoadStateExt;
    chip->UnloadStateExt  = UnloadStateExt;
    chip->SetStartAddress = SetStartAddress3;
    chip->SetSurfaces2D   = nv3SetSurfaces2D;
    chip->SetSurfaces3D   = nv3SetSurfaces3D;
    chip->LockUnlock      = nv3LockUnlock;
पूर्ण
अटल व्योम nv4GetConfig
(
    RIVA_HW_INST *chip
)
अणु
    /*
     * Fill in chip configuration.
     */
    अगर (NV_RD32(chip->PFB, 0x00000000) & 0x00000100)
    अणु
        chip->RamAmountKBytes = ((NV_RD32(chip->PFB, 0x00000000) >> 12) & 0x0F) * 1024 * 2
                              + 1024 * 2;
    पूर्ण
    अन्यथा
    अणु
        चयन (NV_RD32(chip->PFB, 0x00000000) & 0x00000003)
        अणु
            हाल 0:
                chip->RamAmountKBytes = 1024 * 32;
                अवरोध;
            हाल 1:
                chip->RamAmountKBytes = 1024 * 4;
                अवरोध;
            हाल 2:
                chip->RamAmountKBytes = 1024 * 8;
                अवरोध;
            हाल 3:
            शेष:
                chip->RamAmountKBytes = 1024 * 16;
                अवरोध;
        पूर्ण
    पूर्ण
    चयन ((NV_RD32(chip->PFB, 0x00000000) >> 3) & 0x00000003)
    अणु
        हाल 3:
            chip->RamBandwidthKBytesPerSec = 800000;
            अवरोध;
        शेष:
            chip->RamBandwidthKBytesPerSec = 1000000;
            अवरोध;
    पूर्ण
    chip->CrystalFreqKHz   = (NV_RD32(chip->PEXTDEV, 0x00000000) & 0x00000040) ? 14318 : 13500;
    chip->CURSOR           = &(chip->PRAMIN[0x00010000/4 - 0x0800/4]);
    chip->VBlankBit        = 0x00000001;
    chip->MaxVClockFreqKHz = 350000;
    /*
     * Set chip functions.
     */
    chip->Busy            = nv4Busy;
    chip->ShowHideCursor  = ShowHideCursor;
    chip->LoadStateExt    = LoadStateExt;
    chip->UnloadStateExt  = UnloadStateExt;
    chip->SetStartAddress = SetStartAddress;
    chip->SetSurfaces2D   = nv4SetSurfaces2D;
    chip->SetSurfaces3D   = nv4SetSurfaces3D;
    chip->LockUnlock      = nv4LockUnlock;
पूर्ण
अटल व्योम nv10GetConfig
(
    RIVA_HW_INST *chip,
    काष्ठा pci_dev *pdev,
    अचिन्हित पूर्णांक chipset
)
अणु
    काष्ठा pci_dev* dev;
    पूर्णांक करोमुख्य = pci_करोमुख्य_nr(pdev->bus);
    u32 amt;

#अगर_घोषित __BIG_ENDIAN
    /* turn on big endian रेजिस्टर access */
    अगर(!(NV_RD32(chip->PMC, 0x00000004) & 0x01000001))
    	NV_WR32(chip->PMC, 0x00000004, 0x01000001);
#पूर्ण_अगर

    /*
     * Fill in chip configuration.
     */
    अगर(chipset == NV_CHIP_IGEFORCE2) अणु
        dev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 1);
        pci_पढ़ो_config_dword(dev, 0x7C, &amt);
        pci_dev_put(dev);
        chip->RamAmountKBytes = (((amt >> 6) & 31) + 1) * 1024;
    पूर्ण अन्यथा अगर(chipset == NV_CHIP_0x01F0) अणु
        dev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 1);
        pci_पढ़ो_config_dword(dev, 0x84, &amt);
        pci_dev_put(dev);
        chip->RamAmountKBytes = (((amt >> 4) & 127) + 1) * 1024;
    पूर्ण अन्यथा अणु
        चयन ((NV_RD32(chip->PFB, 0x0000020C) >> 20) & 0x000000FF)
        अणु
            हाल 0x02:
                chip->RamAmountKBytes = 1024 * 2;
                अवरोध;
            हाल 0x04:
                chip->RamAmountKBytes = 1024 * 4;
                अवरोध;
            हाल 0x08:
                chip->RamAmountKBytes = 1024 * 8;
                अवरोध;
            हाल 0x10:
                chip->RamAmountKBytes = 1024 * 16;
                अवरोध;
            हाल 0x20:
                chip->RamAmountKBytes = 1024 * 32;
                अवरोध;
            हाल 0x40:
                chip->RamAmountKBytes = 1024 * 64;
                अवरोध;
            हाल 0x80:
                chip->RamAmountKBytes = 1024 * 128;
                अवरोध;
            शेष:
                chip->RamAmountKBytes = 1024 * 16;
                अवरोध;
        पूर्ण
    पूर्ण
    चयन ((NV_RD32(chip->PFB, 0x00000000) >> 3) & 0x00000003)
    अणु
        हाल 3:
            chip->RamBandwidthKBytesPerSec = 800000;
            अवरोध;
        शेष:
            chip->RamBandwidthKBytesPerSec = 1000000;
            अवरोध;
    पूर्ण
    chip->CrystalFreqKHz = (NV_RD32(chip->PEXTDEV, 0x0000) & (1 << 6)) ?
	14318 : 13500;

    चयन (chipset & 0x0ff0) अणु
    हाल 0x0170:
    हाल 0x0180:
    हाल 0x01F0:
    हाल 0x0250:
    हाल 0x0280:
    हाल 0x0300:
    हाल 0x0310:
    हाल 0x0320:
    हाल 0x0330:
    हाल 0x0340:
       अगर(NV_RD32(chip->PEXTDEV, 0x0000) & (1 << 22))
           chip->CrystalFreqKHz = 27000;
       अवरोध;
    शेष:
       अवरोध;
    पूर्ण

    chip->CursorStart      = (chip->RamAmountKBytes - 128) * 1024;
    chip->CURSOR           = शून्य;  /* can't set this here */
    chip->VBlankBit        = 0x00000001;
    chip->MaxVClockFreqKHz = 350000;
    /*
     * Set chip functions.
     */
    chip->Busy            = nv10Busy;
    chip->ShowHideCursor  = ShowHideCursor;
    chip->LoadStateExt    = LoadStateExt;
    chip->UnloadStateExt  = UnloadStateExt;
    chip->SetStartAddress = SetStartAddress;
    chip->SetSurfaces2D   = nv10SetSurfaces2D;
    chip->SetSurfaces3D   = nv10SetSurfaces3D;
    chip->LockUnlock      = nv4LockUnlock;

    चयन(chipset & 0x0ff0) अणु
    हाल 0x0110:
    हाल 0x0170:
    हाल 0x0180:
    हाल 0x01F0:
    हाल 0x0250:
    हाल 0x0280:
    हाल 0x0300:
    हाल 0x0310:
    हाल 0x0320:
    हाल 0x0330:
    हाल 0x0340:
        chip->twoHeads = TRUE;
        अवरोध;
    शेष:
        chip->twoHeads = FALSE;
        अवरोध;
    पूर्ण
पूर्ण
पूर्णांक RivaGetConfig
(
    RIVA_HW_INST *chip,
    काष्ठा pci_dev *pdev,
    अचिन्हित पूर्णांक chipset
)
अणु
    /*
     * Save this so future SW know whats it's dealing with.
     */
    chip->Version = RIVA_SW_VERSION;
    /*
     * Chip specअगरic configuration.
     */
    चयन (chip->Architecture)
    अणु
        हाल NV_ARCH_03:
            nv3GetConfig(chip);
            अवरोध;
        हाल NV_ARCH_04:
            nv4GetConfig(chip);
            अवरोध;
        हाल NV_ARCH_10:
        हाल NV_ARCH_20:
        हाल NV_ARCH_30:
            nv10GetConfig(chip, pdev, chipset);
            अवरोध;
        शेष:
            वापस (-1);
    पूर्ण
    chip->Chipset = chipset;
    /*
     * Fill in FIFO poपूर्णांकers.
     */
    chip->Rop    = (RivaRop __iomem         *)&(chip->FIFO[0x00000000/4]);
    chip->Clip   = (RivaClip __iomem        *)&(chip->FIFO[0x00002000/4]);
    chip->Patt   = (RivaPattern __iomem     *)&(chip->FIFO[0x00004000/4]);
    chip->Pixmap = (RivaPixmap __iomem      *)&(chip->FIFO[0x00006000/4]);
    chip->Blt    = (RivaScreenBlt __iomem   *)&(chip->FIFO[0x00008000/4]);
    chip->Biपंचांगap = (RivaBiपंचांगap __iomem      *)&(chip->FIFO[0x0000A000/4]);
    chip->Line   = (RivaLine __iomem        *)&(chip->FIFO[0x0000C000/4]);
    chip->Tri03  = (RivaTexturedTriangle03 __iomem *)&(chip->FIFO[0x0000E000/4]);
    वापस (0);
पूर्ण

