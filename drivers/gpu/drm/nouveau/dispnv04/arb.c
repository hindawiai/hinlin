<शैली गुरु>
/*
 * Copyright 1993-2003 NVIDIA, Corporation
 * Copyright 2007-2009 Stuart Bennett
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश "nouveau_drv.h"
#समावेश "nouveau_reg.h"
#समावेश "hw.h"

/****************************************************************************\
*                                                                            *
* The video arbitration routines calculate some "magic" numbers.  Fixes      *
* the snow seen when accessing the framebuffer without it.                   *
* It just works (I hope).                                                    *
*                                                                            *
\****************************************************************************/

काष्ठा nv_fअगरo_info अणु
	पूर्णांक lwm;
	पूर्णांक burst;
पूर्ण;

काष्ठा nv_sim_state अणु
	पूर्णांक pclk_khz;
	पूर्णांक mclk_khz;
	पूर्णांक nvclk_khz;
	पूर्णांक bpp;
	पूर्णांक mem_page_miss;
	पूर्णांक mem_latency;
	पूर्णांक memory_type;
	पूर्णांक memory_width;
	पूर्णांक two_heads;
पूर्ण;

अटल व्योम
nv04_calc_arb(काष्ठा nv_fअगरo_info *fअगरo, काष्ठा nv_sim_state *arb)
अणु
	पूर्णांक pagemiss, cas, bpp;
	पूर्णांक nvclks, mclks, crtpagemiss;
	पूर्णांक found, mclk_extra, mclk_loop, cbs, m1, p1;
	पूर्णांक mclk_freq, pclk_freq, nvclk_freq;
	पूर्णांक us_m, us_n, us_p, crtc_drain_rate;
	पूर्णांक cpm_us, us_crt, clwm;

	pclk_freq = arb->pclk_khz;
	mclk_freq = arb->mclk_khz;
	nvclk_freq = arb->nvclk_khz;
	pagemiss = arb->mem_page_miss;
	cas = arb->mem_latency;
	bpp = arb->bpp;
	cbs = 128;

	nvclks = 10;
	mclks = 13 + cas;
	mclk_extra = 3;
	found = 0;

	जबतक (!found) अणु
		found = 1;

		mclk_loop = mclks + mclk_extra;
		us_m = mclk_loop * 1000 * 1000 / mclk_freq;
		us_n = nvclks * 1000 * 1000 / nvclk_freq;
		us_p = nvclks * 1000 * 1000 / pclk_freq;

		crtc_drain_rate = pclk_freq * bpp / 8;
		crtpagemiss = 2;
		crtpagemiss += 1;
		cpm_us = crtpagemiss * pagemiss * 1000 * 1000 / mclk_freq;
		us_crt = cpm_us + us_m + us_n + us_p;
		clwm = us_crt * crtc_drain_rate / (1000 * 1000);
		clwm++;

		m1 = clwm + cbs - 512;
		p1 = m1 * pclk_freq / mclk_freq;
		p1 = p1 * bpp / 8;
		अगर ((p1 < m1 && m1 > 0) || clwm > 519) अणु
			found = !mclk_extra;
			mclk_extra--;
		पूर्ण
		अगर (clwm < 384)
			clwm = 384;

		fअगरo->lwm = clwm;
		fअगरo->burst = cbs;
	पूर्ण
पूर्ण

अटल व्योम
nv10_calc_arb(काष्ठा nv_fअगरo_info *fअगरo, काष्ठा nv_sim_state *arb)
अणु
	पूर्णांक fill_rate, drain_rate;
	पूर्णांक pclks, nvclks, mclks, xclks;
	पूर्णांक pclk_freq, nvclk_freq, mclk_freq;
	पूर्णांक fill_lat, extra_lat;
	पूर्णांक max_burst_o, max_burst_l;
	पूर्णांक fअगरo_len, min_lwm, max_lwm;
	स्थिर पूर्णांक burst_lat = 80; /* Maximum allowable latency due
				   * to the CRTC FIFO burst. (ns) */

	pclk_freq = arb->pclk_khz;
	nvclk_freq = arb->nvclk_khz;
	mclk_freq = arb->mclk_khz;

	fill_rate = mclk_freq * arb->memory_width / 8; /* kB/s */
	drain_rate = pclk_freq * arb->bpp / 8; /* kB/s */

	fअगरo_len = arb->two_heads ? 1536 : 1024; /* B */

	/* Fixed FIFO refill latency. */

	pclks = 4;	/* lwm detect. */

	nvclks = 3	/* lwm -> sync. */
		+ 2	/* fbi bus cycles (1 req + 1 busy) */
		+ 1	/* 2 edge sync.  may be very बंद to edge so
			 * just put one. */
		+ 1	/* fbi_d_rdv_n */
		+ 1	/* Fbi_d_rdata */
		+ 1;	/* crtfअगरo load */

	mclks = 1	/* 2 edge sync.  may be very बंद to edge so
			 * just put one. */
		+ 1	/* arb_hp_req */
		+ 5	/* tiling pipeline */
		+ 2	/* latency fअगरo */
		+ 2	/* memory request to fbio block */
		+ 7;	/* data वापसed from fbio block */

	/* Need to accumulate 256 bits क्रम पढ़ो */
	mclks += (arb->memory_type == 0 ? 2 : 1)
		* arb->memory_width / 32;

	fill_lat = mclks * 1000 * 1000 / mclk_freq   /* minimum mclk latency */
		+ nvclks * 1000 * 1000 / nvclk_freq  /* nvclk latency */
		+ pclks * 1000 * 1000 / pclk_freq;   /* pclk latency */

	/* Conditional FIFO refill latency. */

	xclks = 2 * arb->mem_page_miss + mclks /* Extra latency due to
						* the overlay. */
		+ 2 * arb->mem_page_miss       /* Extra pagemiss latency. */
		+ (arb->bpp == 32 ? 8 : 4);    /* Margin of error. */

	extra_lat = xclks * 1000 * 1000 / mclk_freq;

	अगर (arb->two_heads)
		/* Account क्रम another CRTC. */
		extra_lat += fill_lat + extra_lat + burst_lat;

	/* FIFO burst */

	/* Max burst not leading to overflows. */
	max_burst_o = (1 + fअगरo_len - extra_lat * drain_rate / (1000 * 1000))
		* (fill_rate / 1000) / ((fill_rate - drain_rate) / 1000);
	fअगरo->burst = min(max_burst_o, 1024);

	/* Max burst value with an acceptable latency. */
	max_burst_l = burst_lat * fill_rate / (1000 * 1000);
	fअगरo->burst = min(max_burst_l, fअगरo->burst);

	fअगरo->burst = roundकरोwn_घात_of_two(fअगरo->burst);

	/* FIFO low watermark */

	min_lwm = (fill_lat + extra_lat) * drain_rate / (1000 * 1000) + 1;
	max_lwm = fअगरo_len - fअगरo->burst
		+ fill_lat * drain_rate / (1000 * 1000)
		+ fअगरo->burst * drain_rate / fill_rate;

	fअगरo->lwm = min_lwm + 10 * (max_lwm - min_lwm) / 100; /* Empirical. */
पूर्ण

अटल व्योम
nv04_update_arb(काष्ठा drm_device *dev, पूर्णांक VClk, पूर्णांक bpp,
		पूर्णांक *burst, पूर्णांक *lwm)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvअगर_object *device = &nouveau_drm(dev)->client.device.object;
	काष्ठा nv_fअगरo_info fअगरo_data;
	काष्ठा nv_sim_state sim_data;
	पूर्णांक MClk = nouveau_hw_get_घड़ी(dev, PLL_MEMORY);
	पूर्णांक NVClk = nouveau_hw_get_घड़ी(dev, PLL_CORE);
	uपूर्णांक32_t cfg1 = nvअगर_rd32(device, NV04_PFB_CFG1);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	sim_data.pclk_khz = VClk;
	sim_data.mclk_khz = MClk;
	sim_data.nvclk_khz = NVClk;
	sim_data.bpp = bpp;
	sim_data.two_heads = nv_two_heads(dev);
	अगर ((pdev->device & 0xffff) == 0x01a0 /*CHIPSET_NFORCE*/ ||
	    (pdev->device & 0xffff) == 0x01f0 /*CHIPSET_NFORCE2*/) अणु
		uपूर्णांक32_t type;
		पूर्णांक करोमुख्य = pci_करोमुख्य_nr(pdev->bus);

		pci_पढ़ो_config_dword(pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 1),
				      0x7c, &type);

		sim_data.memory_type = (type >> 12) & 1;
		sim_data.memory_width = 64;
		sim_data.mem_latency = 3;
		sim_data.mem_page_miss = 10;
	पूर्ण अन्यथा अणु
		sim_data.memory_type = nvअगर_rd32(device, NV04_PFB_CFG0) & 0x1;
		sim_data.memory_width = (nvअगर_rd32(device, NV_PEXTDEV_BOOT_0) & 0x10) ? 128 : 64;
		sim_data.mem_latency = cfg1 & 0xf;
		sim_data.mem_page_miss = ((cfg1 >> 4) & 0xf) + ((cfg1 >> 31) & 0x1);
	पूर्ण

	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_TNT)
		nv04_calc_arb(&fअगरo_data, &sim_data);
	अन्यथा
		nv10_calc_arb(&fअगरo_data, &sim_data);

	*burst = ilog2(fअगरo_data.burst >> 4);
	*lwm = fअगरo_data.lwm >> 3;
पूर्ण

अटल व्योम
nv20_update_arb(पूर्णांक *burst, पूर्णांक *lwm)
अणु
	अचिन्हित पूर्णांक fअगरo_size, burst_size, graphics_lwm;

	fअगरo_size = 2048;
	burst_size = 512;
	graphics_lwm = fअगरo_size - burst_size;

	*burst = ilog2(burst_size >> 5);
	*lwm = graphics_lwm >> 3;
पूर्ण

व्योम
nouveau_calc_arb(काष्ठा drm_device *dev, पूर्णांक vclk, पूर्णांक bpp, पूर्णांक *burst, पूर्णांक *lwm)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_KELVIN)
		nv04_update_arb(dev, vclk, bpp, burst, lwm);
	अन्यथा अगर ((pdev->device & 0xfff0) == 0x0240 /*CHIPSET_C51*/ ||
		 (pdev->device & 0xfff0) == 0x03d0 /*CHIPSET_C512*/) अणु
		*burst = 128;
		*lwm = 0x0480;
	पूर्ण अन्यथा
		nv20_update_arb(burst, lwm);
पूर्ण
