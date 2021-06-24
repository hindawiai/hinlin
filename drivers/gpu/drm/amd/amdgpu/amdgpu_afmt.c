<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Christian Kथघnig.
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
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Christian Kथघnig
 */
#समावेश <linux/hdmi.h>
#समावेश <linux/gcd.h>

#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"

अटल स्थिर काष्ठा amdgpu_afmt_acr amdgpu_afmt_predefined_acr[] = अणु
    /*	     32kHz	  44.1kHz	48kHz    */
    /* Clock      N     CTS      N     CTS      N     CTS */
    अणु  25175,  4096,  25175, 28224, 125875,  6144,  25175 पूर्ण, /*  25,20/1.001 MHz */
    अणु  25200,  4096,  25200,  6272,  28000,  6144,  25200 पूर्ण, /*  25.20       MHz */
    अणु  27000,  4096,  27000,  6272,  30000,  6144,  27000 पूर्ण, /*  27.00       MHz */
    अणु  27027,  4096,  27027,  6272,  30030,  6144,  27027 पूर्ण, /*  27.00*1.001 MHz */
    अणु  54000,  4096,  54000,  6272,  60000,  6144,  54000 पूर्ण, /*  54.00       MHz */
    अणु  54054,  4096,  54054,  6272,  60060,  6144,  54054 पूर्ण, /*  54.00*1.001 MHz */
    अणु  74176,  4096,  74176,  5733,  75335,  6144,  74176 पूर्ण, /*  74.25/1.001 MHz */
    अणु  74250,  4096,  74250,  6272,  82500,  6144,  74250 पूर्ण, /*  74.25       MHz */
    अणु 148352,  4096, 148352,  5733, 150670,  6144, 148352 पूर्ण, /* 148.50/1.001 MHz */
    अणु 148500,  4096, 148500,  6272, 165000,  6144, 148500 पूर्ण, /* 148.50       MHz */
पूर्ण;


/*
 * calculate CTS and N values अगर they are not found in the table
 */
अटल व्योम amdgpu_afmt_calc_cts(uपूर्णांक32_t घड़ी, पूर्णांक *CTS, पूर्णांक *N, पूर्णांक freq)
अणु
	पूर्णांक n, cts;
	अचिन्हित दीर्घ भाग, mul;

	/* Safe, but overly large values */
	n = 128 * freq;
	cts = घड़ी * 1000;

	/* Smallest valid fraction */
	भाग = gcd(n, cts);

	n /= भाग;
	cts /= भाग;

	/*
	 * The optimal N is 128*freq/1000. Calculate the बंदst larger
	 * value that करोesn't truncate any bits.
	 */
	mul = ((128*freq/1000) + (n-1))/n;

	n *= mul;
	cts *= mul;

	/* Check that we are in spec (not always possible) */
	अगर (n < (128*freq/1500))
		pr_warn("Calculated ACR N value is too small. You may experience audio problems.\n");
	अगर (n > (128*freq/300))
		pr_warn("Calculated ACR N value is too large. You may experience audio problems.\n");

	*N = n;
	*CTS = cts;

	DRM_DEBUG("Calculated ACR timing N=%d CTS=%d for frequency %d\n",
		  *N, *CTS, freq);
पूर्ण

काष्ठा amdgpu_afmt_acr amdgpu_afmt_acr(uपूर्णांक32_t घड़ी)
अणु
	काष्ठा amdgpu_afmt_acr res;
	u8 i;

	/* Precalculated values क्रम common घड़ीs */
	क्रम (i = 0; i < ARRAY_SIZE(amdgpu_afmt_predefined_acr); i++) अणु
		अगर (amdgpu_afmt_predefined_acr[i].घड़ी == घड़ी)
			वापस amdgpu_afmt_predefined_acr[i];
	पूर्ण

	/* And odd घड़ीs get manually calculated */
	amdgpu_afmt_calc_cts(घड़ी, &res.cts_32khz, &res.n_32khz, 32000);
	amdgpu_afmt_calc_cts(घड़ी, &res.cts_44_1khz, &res.n_44_1khz, 44100);
	amdgpu_afmt_calc_cts(घड़ी, &res.cts_48khz, &res.n_48khz, 48000);

	वापस res;
पूर्ण
