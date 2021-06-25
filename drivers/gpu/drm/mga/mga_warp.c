<शैली गुरु>
/* mga_warp.c -- Matrox G200/G400 WARP engine management -*- linux-c -*-
 * Created: Thu Jan 11 21:29:32 2001 by gareth@valinux.com
 *
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Gareth Hughes <gareth@valinux.com>
 */

#समावेश <linux/firmware.h>
#समावेश <linux/ihex.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "mga_drv.h"

#घोषणा FIRMWARE_G200 "matrox/g200_warp.fw"
#घोषणा FIRMWARE_G400 "matrox/g400_warp.fw"

MODULE_FIRMWARE(FIRMWARE_G200);
MODULE_FIRMWARE(FIRMWARE_G400);

#घोषणा MGA_WARP_CODE_ALIGN		256	/* in bytes */

#घोषणा WARP_UCODE_SIZE(size)		ALIGN(size, MGA_WARP_CODE_ALIGN)

पूर्णांक mga_warp_install_microcode(drm_mga_निजी_t *dev_priv)
अणु
	अचिन्हित अक्षर *vcbase = dev_priv->warp->handle;
	अचिन्हित दीर्घ pcbase = dev_priv->warp->offset;
	स्थिर अक्षर *firmware_name;
	काष्ठा platक्रमm_device *pdev;
	स्थिर काष्ठा firmware *fw = शून्य;
	स्थिर काष्ठा ihex_binrec *rec;
	अचिन्हित पूर्णांक size;
	पूर्णांक n_pipes, where;
	पूर्णांक rc = 0;

	चयन (dev_priv->chipset) अणु
	हाल MGA_CARD_TYPE_G400:
	हाल MGA_CARD_TYPE_G550:
		firmware_name = FIRMWARE_G400;
		n_pipes = MGA_MAX_G400_PIPES;
		अवरोध;
	हाल MGA_CARD_TYPE_G200:
		firmware_name = FIRMWARE_G200;
		n_pipes = MGA_MAX_G200_PIPES;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pdev = platक्रमm_device_रेजिस्टर_simple("mga_warp", 0, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		DRM_ERROR("mga: Failed to register microcode\n");
		वापस PTR_ERR(pdev);
	पूर्ण
	rc = request_ihex_firmware(&fw, firmware_name, &pdev->dev);
	platक्रमm_device_unरेजिस्टर(pdev);
	अगर (rc) अणु
		DRM_ERROR("mga: Failed to load microcode \"%s\"\n",
			  firmware_name);
		वापस rc;
	पूर्ण

	size = 0;
	where = 0;
	क्रम (rec = (स्थिर काष्ठा ihex_binrec *)fw->data;
	     rec;
	     rec = ihex_next_binrec(rec)) अणु
		size += WARP_UCODE_SIZE(be16_to_cpu(rec->len));
		where++;
	पूर्ण

	अगर (where != n_pipes) अणु
		DRM_ERROR("mga: Invalid microcode \"%s\"\n", firmware_name);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	size = PAGE_ALIGN(size);
	DRM_DEBUG("MGA ucode size = %d bytes\n", size);
	अगर (size > dev_priv->warp->size) अणु
		DRM_ERROR("microcode too large! (%u > %lu)\n",
			  size, dev_priv->warp->size);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	स_रखो(dev_priv->warp_pipe_phys, 0, माप(dev_priv->warp_pipe_phys));

	where = 0;
	क्रम (rec = (स्थिर काष्ठा ihex_binrec *)fw->data;
	     rec;
	     rec = ihex_next_binrec(rec)) अणु
		अचिन्हित पूर्णांक src_size, dst_size;

		DRM_DEBUG(" pcbase = 0x%08lx  vcbase = %p\n", pcbase, vcbase);
		dev_priv->warp_pipe_phys[where] = pcbase;
		src_size = be16_to_cpu(rec->len);
		dst_size = WARP_UCODE_SIZE(src_size);
		स_नकल(vcbase, rec->data, src_size);
		pcbase += dst_size;
		vcbase += dst_size;
		where++;
	पूर्ण

out:
	release_firmware(fw);
	वापस rc;
पूर्ण

#घोषणा WMISC_EXPECTED		(MGA_WUCODECACHE_ENABLE | MGA_WMASTER_ENABLE)

पूर्णांक mga_warp_init(drm_mga_निजी_t *dev_priv)
अणु
	u32 wmisc;

	/* FIXME: Get rid of these damned magic numbers...
	 */
	चयन (dev_priv->chipset) अणु
	हाल MGA_CARD_TYPE_G400:
	हाल MGA_CARD_TYPE_G550:
		MGA_WRITE(MGA_WIADDR2, MGA_WMODE_SUSPEND);
		MGA_WRITE(MGA_WGETMSB, 0x00000E00);
		MGA_WRITE(MGA_WVRTXSZ, 0x00001807);
		MGA_WRITE(MGA_WACCEPTSEQ, 0x18000000);
		अवरोध;
	हाल MGA_CARD_TYPE_G200:
		MGA_WRITE(MGA_WIADDR, MGA_WMODE_SUSPEND);
		MGA_WRITE(MGA_WGETMSB, 0x1606);
		MGA_WRITE(MGA_WVRTXSZ, 7);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	MGA_WRITE(MGA_WMISC, (MGA_WUCODECACHE_ENABLE |
			      MGA_WMASTER_ENABLE | MGA_WCACHEFLUSH_ENABLE));
	wmisc = MGA_READ(MGA_WMISC);
	अगर (wmisc != WMISC_EXPECTED) अणु
		DRM_ERROR("WARP engine config failed! 0x%x != 0x%x\n",
			  wmisc, WMISC_EXPECTED);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
