<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * This is "two-way" पूर्णांकerface, acting as the SHIM layer between driver
 * and PHY layer. The driver can optionally call this translation layer
 * to करो some preprocessing, then reach PHY. On the PHY->driver direction,
 * all calls go through this layer since PHY करोesn't have access to the
 * driver's brcms_hardware poपूर्णांकer.
 */
#समावेश <linux/slab.h>
#समावेश <net/mac80211.h>

#समावेश "main.h"
#समावेश "mac80211_if.h"
#समावेश "phy_shim.h"

/* PHY SHIM module specअगरic state */
काष्ठा phy_shim_info अणु
	काष्ठा brcms_hardware *wlc_hw;	/* poपूर्णांकer to मुख्य wlc_hw काष्ठाure */
	काष्ठा brcms_c_info *wlc;	/* poपूर्णांकer to मुख्य wlc काष्ठाure */
	काष्ठा brcms_info *wl; /* poपूर्णांकer to os-specअगरic निजी state */
पूर्ण;

काष्ठा phy_shim_info *wlc_phy_shim_attach(काष्ठा brcms_hardware *wlc_hw,
					  काष्ठा brcms_info *wl,
					  काष्ठा brcms_c_info *wlc) अणु
	काष्ठा phy_shim_info *physhim = शून्य;

	physhim = kzalloc(माप(काष्ठा phy_shim_info), GFP_ATOMIC);
	अगर (!physhim)
		वापस शून्य;

	physhim->wlc_hw = wlc_hw;
	physhim->wlc = wlc;
	physhim->wl = wl;

	वापस physhim;
पूर्ण

व्योम wlc_phy_shim_detach(काष्ठा phy_shim_info *physhim)
अणु
	kमुक्त(physhim);
पूर्ण

काष्ठा wlapi_समयr *wlapi_init_समयr(काष्ठा phy_shim_info *physhim,
				     व्योम (*fn)(काष्ठा brcms_phy *pi),
				     व्योम *arg, स्थिर अक्षर *name)
अणु
	वापस (काष्ठा wlapi_समयr *)
			brcms_init_समयr(physhim->wl, (व्योम (*)(व्योम *))fn,
					 arg, name);
पूर्ण

व्योम wlapi_मुक्त_समयr(काष्ठा wlapi_समयr *t)
अणु
	brcms_मुक्त_समयr((काष्ठा brcms_समयr *)t);
पूर्ण

व्योम
wlapi_add_समयr(काष्ठा wlapi_समयr *t, uपूर्णांक ms, पूर्णांक periodic)
अणु
	brcms_add_समयr((काष्ठा brcms_समयr *)t, ms, periodic);
पूर्ण

bool wlapi_del_समयr(काष्ठा wlapi_समयr *t)
अणु
	वापस brcms_del_समयr((काष्ठा brcms_समयr *)t);
पूर्ण

व्योम wlapi_पूर्णांकrson(काष्ठा phy_shim_info *physhim)
अणु
	brcms_पूर्णांकrson(physhim->wl);
पूर्ण

u32 wlapi_पूर्णांकrsoff(काष्ठा phy_shim_info *physhim)
अणु
	वापस brcms_पूर्णांकrsoff(physhim->wl);
पूर्ण

व्योम wlapi_पूर्णांकrsrestore(काष्ठा phy_shim_info *physhim, u32 macपूर्णांकmask)
अणु
	brcms_पूर्णांकrsrestore(physhim->wl, macपूर्णांकmask);
पूर्ण

व्योम wlapi_bmac_ग_लिखो_shm(काष्ठा phy_shim_info *physhim, uपूर्णांक offset, u16 v)
अणु
	brcms_b_ग_लिखो_shm(physhim->wlc_hw, offset, v);
पूर्ण

u16 wlapi_bmac_पढ़ो_shm(काष्ठा phy_shim_info *physhim, uपूर्णांक offset)
अणु
	वापस brcms_b_पढ़ो_shm(physhim->wlc_hw, offset);
पूर्ण

व्योम
wlapi_bmac_mhf(काष्ठा phy_shim_info *physhim, u8 idx, u16 mask,
	       u16 val, पूर्णांक bands)
अणु
	brcms_b_mhf(physhim->wlc_hw, idx, mask, val, bands);
पूर्ण

व्योम wlapi_bmac_corereset(काष्ठा phy_shim_info *physhim, u32 flags)
अणु
	brcms_b_corereset(physhim->wlc_hw, flags);
पूर्ण

व्योम wlapi_suspend_mac_and_रुको(काष्ठा phy_shim_info *physhim)
अणु
	brcms_c_suspend_mac_and_रुको(physhim->wlc);
पूर्ण

व्योम wlapi_चयन_macfreq(काष्ठा phy_shim_info *physhim, u8 spurmode)
अणु
	brcms_b_चयन_macfreq(physhim->wlc_hw, spurmode);
पूर्ण

व्योम wlapi_enable_mac(काष्ठा phy_shim_info *physhim)
अणु
	brcms_c_enable_mac(physhim->wlc);
पूर्ण

व्योम wlapi_bmac_mctrl(काष्ठा phy_shim_info *physhim, u32 mask, u32 val)
अणु
	brcms_b_mctrl(physhim->wlc_hw, mask, val);
पूर्ण

व्योम wlapi_bmac_phy_reset(काष्ठा phy_shim_info *physhim)
अणु
	brcms_b_phy_reset(physhim->wlc_hw);
पूर्ण

व्योम wlapi_bmac_bw_set(काष्ठा phy_shim_info *physhim, u16 bw)
अणु
	brcms_b_bw_set(physhim->wlc_hw, bw);
पूर्ण

u16 wlapi_bmac_get_txant(काष्ठा phy_shim_info *physhim)
अणु
	वापस brcms_b_get_txant(physhim->wlc_hw);
पूर्ण

व्योम wlapi_bmac_phyclk_fgc(काष्ठा phy_shim_info *physhim, bool clk)
अणु
	brcms_b_phyclk_fgc(physhim->wlc_hw, clk);
पूर्ण

व्योम wlapi_bmac_macphyclk_set(काष्ठा phy_shim_info *physhim, bool clk)
अणु
	brcms_b_macphyclk_set(physhim->wlc_hw, clk);
पूर्ण

व्योम wlapi_bmac_core_phypll_ctl(काष्ठा phy_shim_info *physhim, bool on)
अणु
	brcms_b_core_phypll_ctl(physhim->wlc_hw, on);
पूर्ण

व्योम wlapi_bmac_core_phypll_reset(काष्ठा phy_shim_info *physhim)
अणु
	brcms_b_core_phypll_reset(physhim->wlc_hw);
पूर्ण

व्योम wlapi_bmac_ucode_wake_override_phyreg_set(काष्ठा phy_shim_info *physhim)
अणु
	brcms_c_ucode_wake_override_set(physhim->wlc_hw,
					BRCMS_WAKE_OVERRIDE_PHYREG);
पूर्ण

व्योम wlapi_bmac_ucode_wake_override_phyreg_clear(काष्ठा phy_shim_info *physhim)
अणु
	brcms_c_ucode_wake_override_clear(physhim->wlc_hw,
					  BRCMS_WAKE_OVERRIDE_PHYREG);
पूर्ण

व्योम
wlapi_bmac_ग_लिखो_ढाँचा_ram(काष्ठा phy_shim_info *physhim, पूर्णांक offset,
			      पूर्णांक len, व्योम *buf)
अणु
	brcms_b_ग_लिखो_ढाँचा_ram(physhim->wlc_hw, offset, len, buf);
पूर्ण

u16 wlapi_bmac_rate_shm_offset(काष्ठा phy_shim_info *physhim, u8 rate)
अणु
	वापस brcms_b_rate_shm_offset(physhim->wlc_hw, rate);
पूर्ण

व्योम wlapi_ucode_sample_init(काष्ठा phy_shim_info *physhim)
अणु
पूर्ण

व्योम
wlapi_copyfrom_objmem(काष्ठा phy_shim_info *physhim, uपूर्णांक offset, व्योम *buf,
		      पूर्णांक len, u32 sel)
अणु
	brcms_b_copyfrom_objmem(physhim->wlc_hw, offset, buf, len, sel);
पूर्ण

व्योम
wlapi_copyto_objmem(काष्ठा phy_shim_info *physhim, uपूर्णांक offset, स्थिर व्योम *buf,
		    पूर्णांक l, u32 sel)
अणु
	brcms_b_copyto_objmem(physhim->wlc_hw, offset, buf, l, sel);
पूर्ण
