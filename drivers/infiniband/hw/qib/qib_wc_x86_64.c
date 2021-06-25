<शैली गुरु>
/*
 * Copyright (c) 2012 Intel Corporation. All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation. All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * This file is conditionally built on x86_64 only.  Otherwise weak symbol
 * versions of the functions exported from here are used.
 */

#समावेश <linux/pci.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/processor.h>

#समावेश "qib.h"

/**
 * qib_enable_wc - enable ग_लिखो combining क्रम MMIO ग_लिखोs to the device
 * @dd: qlogic_ib device
 *
 * This routine is x86_64-specअगरic; it twiddles the CPU's MTRRs to enable
 * ग_लिखो combining.
 */
पूर्णांक qib_enable_wc(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret = 0;
	u64 pioaddr, piolen;
	अचिन्हित bits;
	स्थिर अचिन्हित दीर्घ addr = pci_resource_start(dd->pcidev, 0);
	स्थिर माप_प्रकार len = pci_resource_len(dd->pcidev, 0);

	/*
	 * Set the PIO buffers to be WCCOMB, so we get HT bursts to the
	 * chip.  Linux (possibly the hardware) requires it to be on a घातer
	 * of 2 address matching the length (which has to be a घातer of 2).
	 * For rev1, that means the base address, क्रम rev2, it will be just
	 * the PIO buffers themselves.
	 * For chips with two sets of buffers, the calculations are
	 * somewhat more complicated; we need to sum, and the piobufbase
	 * रेजिस्टर has both offsets, 2K in low 32 bits, 4K in high 32 bits.
	 * The buffers are still packed, so a single range covers both.
	 */
	अगर (dd->piobcnt2k && dd->piobcnt4k) अणु
		/* 2 sizes क्रम chip */
		अचिन्हित दीर्घ pio2kbase, pio4kbase;

		pio2kbase = dd->piobufbase & 0xffffffffUL;
		pio4kbase = (dd->piobufbase >> 32) & 0xffffffffUL;
		अगर (pio2kbase < pio4kbase) अणु
			/* all current chips */
			pioaddr = addr + pio2kbase;
			piolen = pio4kbase - pio2kbase +
				dd->piobcnt4k * dd->align4k;
		पूर्ण अन्यथा अणु
			pioaddr = addr + pio4kbase;
			piolen = pio2kbase - pio4kbase +
				dd->piobcnt2k * dd->palign;
		पूर्ण
	पूर्ण अन्यथा अणु  /* single buffer size (2K, currently) */
		pioaddr = addr + dd->piobufbase;
		piolen = dd->piobcnt2k * dd->palign +
			dd->piobcnt4k * dd->align4k;
	पूर्ण

	क्रम (bits = 0; !(piolen & (1ULL << bits)); bits++)
		; /* करो nothing */

	अगर (piolen != (1ULL << bits)) अणु
		piolen >>= bits;
		जबतक (piolen >>= 1)
			bits++;
		piolen = 1ULL << (bits + 1);
	पूर्ण
	अगर (pioaddr & (piolen - 1)) अणु
		u64 aपंचांगp = pioaddr & ~(piolen - 1);

		अगर (aपंचांगp < addr || (aपंचांगp + piolen) > (addr + len)) अणु
			qib_dev_err(dd,
				"No way to align address/size (%llx/%llx), no WC mtrr\n",
				(अचिन्हित दीर्घ दीर्घ) aपंचांगp,
				(अचिन्हित दीर्घ दीर्घ) piolen << 1);
			ret = -ENODEV;
		पूर्ण अन्यथा अणु
			pioaddr = aपंचांगp;
			piolen <<= 1;
		पूर्ण
	पूर्ण

	अगर (!ret) अणु
		dd->wc_cookie = arch_phys_wc_add(pioaddr, piolen);
		अगर (dd->wc_cookie < 0)
			/* use error from routine */
			ret = dd->wc_cookie;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * qib_disable_wc - disable ग_लिखो combining क्रम MMIO ग_लिखोs to the device
 * @dd: qlogic_ib device
 */
व्योम qib_disable_wc(काष्ठा qib_devdata *dd)
अणु
	arch_phys_wc_del(dd->wc_cookie);
पूर्ण

/**
 * qib_unordered_wc - indicate whether ग_लिखो combining is ordered
 *
 * Because our perक्रमmance depends on our ability to करो ग_लिखो combining mmio
 * ग_लिखोs in the most efficient way, we need to know अगर we are on an Intel
 * or AMD x86_64 processor.  AMD x86_64 processors flush WC buffers out in
 * the order completed, and so no special flushing is required to get
 * correct ordering.  Intel processors, however, will flush ग_लिखो buffers
 * out in "random" orders, and so explicit ordering is needed at बार.
 */
पूर्णांक qib_unordered_wc(व्योम)
अणु
	वापस boot_cpu_data.x86_venकरोr != X86_VENDOR_AMD;
पूर्ण
