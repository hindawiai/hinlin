<शैली गुरु>
/*
 * Copyright 2011 Intel Corporation
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#समावेश <linux/acpi.h>
#समावेश "psb_drv.h"
#समावेश "psb_intel_reg.h"

#घोषणा PCI_ASLE 0xe4
#घोषणा PCI_ASLS 0xfc

#घोषणा OPREGION_HEADER_OFFSET 0
#घोषणा OPREGION_ACPI_OFFSET   0x100
#घोषणा   ACPI_CLID 0x01ac /* current lid state indicator */
#घोषणा   ACPI_CDCK 0x01b0 /* current करोcking state indicator */
#घोषणा OPREGION_SWSCI_OFFSET  0x200
#घोषणा OPREGION_ASLE_OFFSET   0x300
#घोषणा OPREGION_VBT_OFFSET    0x400

#घोषणा OPREGION_SIGNATURE "IntelGraphicsMem"
#घोषणा MBOX_ACPI      (1<<0)
#घोषणा MBOX_SWSCI     (1<<1)
#घोषणा MBOX_ASLE      (1<<2)

काष्ठा opregion_header अणु
	u8 signature[16];
	u32 size;
	u32 opregion_ver;
	u8 bios_ver[32];
	u8 vbios_ver[16];
	u8 driver_ver[16];
	u32 mboxes;
	u8 reserved[164];
पूर्ण __packed;

/* OpRegion mailbox #1: खुला ACPI methods */
काष्ठा opregion_acpi अणु
	u32 drdy;	/* driver पढ़ोiness */
	u32 csts;	/* notअगरication status */
	u32 cevt;	/* current event */
	u8 rsvd1[20];
	u32 didl[8];	/* supported display devices ID list */
	u32 cpdl[8];	/* currently presented display list */
	u32 cadl[8];	/* currently active display list */
	u32 nadl[8];	/* next active devices list */
	u32 aslp;	/* ASL sleep समय-out */
	u32 tidx;	/* toggle table index */
	u32 chpd;	/* current hotplug enable indicator */
	u32 clid;	/* current lid state*/
	u32 cdck;	/* current करोcking state */
	u32 sxsw;	/* Sx state resume */
	u32 evts;	/* ASL supported events */
	u32 cnot;	/* current OS notअगरication */
	u32 nrdy;	/* driver status */
	u8 rsvd2[60];
पूर्ण __packed;

/* OpRegion mailbox #2: SWSCI */
काष्ठा opregion_swsci अणु
	/*FIXME: add it later*/
पूर्ण __packed;

/* OpRegion mailbox #3: ASLE */
काष्ठा opregion_asle अणु
	u32 ardy;	/* driver पढ़ोiness */
	u32 aslc;	/* ASLE पूर्णांकerrupt command */
	u32 tche;	/* technology enabled indicator */
	u32 alsi;	/* current ALS illuminance पढ़ोing */
	u32 bclp;	/* backlight brightness to set */
	u32 pfit;	/* panel fitting state */
	u32 cblv;	/* current brightness level */
	u16 bclm[20];	/* backlight level duty cycle mapping table */
	u32 cpfm;	/* current panel fitting mode */
	u32 epfm;	/* enabled panel fitting modes */
	u8 plut[74];	/* panel LUT and identअगरier */
	u32 pfmb;	/* PWM freq and min brightness */
	u8 rsvd[102];
पूर्ण __packed;

/* ASLE irq request bits */
#घोषणा ASLE_SET_ALS_ILLUM     (1 << 0)
#घोषणा ASLE_SET_BACKLIGHT     (1 << 1)
#घोषणा ASLE_SET_PFIT          (1 << 2)
#घोषणा ASLE_SET_PWM_FREQ      (1 << 3)
#घोषणा ASLE_REQ_MSK           0xf

/* response bits of ASLE irq request */
#घोषणा ASLE_ALS_ILLUM_FAILED   (1<<10)
#घोषणा ASLE_BACKLIGHT_FAILED   (1<<12)
#घोषणा ASLE_PFIT_FAILED        (1<<14)
#घोषणा ASLE_PWM_FREQ_FAILED    (1<<16)

/* ASLE backlight brightness to set */
#घोषणा ASLE_BCLP_VALID                (1<<31)
#घोषणा ASLE_BCLP_MSK          (~(1<<31))

/* ASLE panel fitting request */
#घोषणा ASLE_PFIT_VALID         (1<<31)
#घोषणा ASLE_PFIT_CENTER (1<<0)
#घोषणा ASLE_PFIT_STRETCH_TEXT (1<<1)
#घोषणा ASLE_PFIT_STRETCH_GFX (1<<2)

/* response bits of ASLE irq request */
#घोषणा ASLE_ALS_ILLUM_FAILED	(1<<10)
#घोषणा ASLE_BACKLIGHT_FAILED	(1<<12)
#घोषणा ASLE_PFIT_FAILED	(1<<14)
#घोषणा ASLE_PWM_FREQ_FAILED	(1<<16)

/* ASLE backlight brightness to set */
#घोषणा ASLE_BCLP_VALID                (1<<31)
#घोषणा ASLE_BCLP_MSK          (~(1<<31))

/* ASLE panel fitting request */
#घोषणा ASLE_PFIT_VALID         (1<<31)
#घोषणा ASLE_PFIT_CENTER (1<<0)
#घोषणा ASLE_PFIT_STRETCH_TEXT (1<<1)
#घोषणा ASLE_PFIT_STRETCH_GFX (1<<2)

/* PWM frequency and minimum brightness */
#घोषणा ASLE_PFMB_BRIGHTNESS_MASK (0xff)
#घोषणा ASLE_PFMB_BRIGHTNESS_VALID (1<<8)
#घोषणा ASLE_PFMB_PWM_MASK (0x7ffffe00)
#घोषणा ASLE_PFMB_PWM_VALID (1<<31)

#घोषणा ASLE_CBLV_VALID         (1<<31)

अटल काष्ठा psb_पूर्णांकel_opregion *प्रणाली_opregion;

अटल u32 asle_set_backlight(काष्ठा drm_device *dev, u32 bclp)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा opregion_asle *asle = dev_priv->opregion.asle;
	काष्ठा backlight_device *bd = dev_priv->backlight_device;

	DRM_DEBUG_DRIVER("asle set backlight %x\n", bclp);

	अगर (!(bclp & ASLE_BCLP_VALID))
		वापस ASLE_BACKLIGHT_FAILED;

	अगर (bd == शून्य)
		वापस ASLE_BACKLIGHT_FAILED;

	bclp &= ASLE_BCLP_MSK;
	अगर (bclp > 255)
		वापस ASLE_BACKLIGHT_FAILED;

	gma_backlight_set(dev, bclp * bd->props.max_brightness / 255);

	asle->cblv = (bclp * 0x64) / 0xff | ASLE_CBLV_VALID;

	वापस 0;
पूर्ण

अटल व्योम psb_पूर्णांकel_opregion_asle_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा psb_पूर्णांकel_opregion *opregion =
		container_of(work, काष्ठा psb_पूर्णांकel_opregion, asle_work);
	काष्ठा drm_psb_निजी *dev_priv =
		container_of(opregion, काष्ठा drm_psb_निजी, opregion);
	काष्ठा opregion_asle *asle = opregion->asle;
	u32 asle_stat = 0;
	u32 asle_req;

	अगर (!asle)
		वापस;

	asle_req = asle->aslc & ASLE_REQ_MSK;
	अगर (!asle_req) अणु
		DRM_DEBUG_DRIVER("non asle set request??\n");
		वापस;
	पूर्ण

	अगर (asle_req & ASLE_SET_BACKLIGHT)
		asle_stat |= asle_set_backlight(dev_priv->dev, asle->bclp);

	asle->aslc = asle_stat;

पूर्ण

व्योम psb_पूर्णांकel_opregion_asle_पूर्णांकr(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	अगर (dev_priv->opregion.asle)
		schedule_work(&dev_priv->opregion.asle_work);
पूर्ण

#घोषणा ASLE_ALS_EN    (1<<0)
#घोषणा ASLE_BLC_EN    (1<<1)
#घोषणा ASLE_PFIT_EN   (1<<2)
#घोषणा ASLE_PFMB_EN   (1<<3)

व्योम psb_पूर्णांकel_opregion_enable_asle(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा opregion_asle *asle = dev_priv->opregion.asle;

	अगर (asle && प्रणाली_opregion ) अणु
		/* Don't करो this on Medfield or other non PC like devices, they
		   use the bit क्रम something dअगरferent altogether */
		psb_enable_pipestat(dev_priv, 0, PIPE_LEGACY_BLC_EVENT_ENABLE);
		psb_enable_pipestat(dev_priv, 1, PIPE_LEGACY_BLC_EVENT_ENABLE);

		asle->tche = ASLE_ALS_EN | ASLE_BLC_EN | ASLE_PFIT_EN
								| ASLE_PFMB_EN;
		asle->ardy = 1;
	पूर्ण
पूर्ण

#घोषणा ACPI_EV_DISPLAY_SWITCH (1<<0)
#घोषणा ACPI_EV_LID            (1<<1)
#घोषणा ACPI_EV_DOCK           (1<<2)


अटल पूर्णांक psb_पूर्णांकel_opregion_video_event(काष्ठा notअगरier_block *nb,
					  अचिन्हित दीर्घ val, व्योम *data)
अणु
	/* The only video events relevant to opregion are 0x80. These indicate
	   either a करोcking event, lid चयन or display चयन request. In
	   Linux, these are handled by the करोck, button and video drivers.
	   We might want to fix the video driver to be opregion-aware in
	   future, but right now we just indicate to the firmware that the
	   request has been handled */

	काष्ठा opregion_acpi *acpi;

	अगर (!प्रणाली_opregion)
		वापस NOTIFY_DONE;

	acpi = प्रणाली_opregion->acpi;
	acpi->csts = 0;

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block psb_पूर्णांकel_opregion_notअगरier = अणु
	.notअगरier_call = psb_पूर्णांकel_opregion_video_event,
पूर्ण;

व्योम psb_पूर्णांकel_opregion_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_पूर्णांकel_opregion *opregion = &dev_priv->opregion;

	अगर (!opregion->header)
		वापस;

	अगर (opregion->acpi) अणु
		/* Notअगरy BIOS we are पढ़ोy to handle ACPI video ext notअगरs.
		 * Right now, all the events are handled by the ACPI video
		 * module. We करोn't actually need to करो anything with them. */
		opregion->acpi->csts = 0;
		opregion->acpi->drdy = 1;

		प्रणाली_opregion = opregion;
		रेजिस्टर_acpi_notअगरier(&psb_पूर्णांकel_opregion_notअगरier);
	पूर्ण
पूर्ण

व्योम psb_पूर्णांकel_opregion_fini(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_पूर्णांकel_opregion *opregion = &dev_priv->opregion;

	अगर (!opregion->header)
		वापस;

	अगर (opregion->acpi) अणु
		opregion->acpi->drdy = 0;

		प्रणाली_opregion = शून्य;
		unरेजिस्टर_acpi_notअगरier(&psb_पूर्णांकel_opregion_notअगरier);
	पूर्ण

	cancel_work_sync(&opregion->asle_work);

	/* just clear all opregion memory poपूर्णांकers now */
	iounmap(opregion->header);
	opregion->header = शून्य;
	opregion->acpi = शून्य;
	opregion->swsci = शून्य;
	opregion->asle = शून्य;
	opregion->vbt = शून्य;
पूर्ण

पूर्णांक psb_पूर्णांकel_opregion_setup(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा psb_पूर्णांकel_opregion *opregion = &dev_priv->opregion;
	u32 opregion_phy, mboxes;
	व्योम __iomem *base;
	पूर्णांक err = 0;

	pci_पढ़ो_config_dword(pdev, PCI_ASLS, &opregion_phy);
	अगर (opregion_phy == 0) अणु
		DRM_DEBUG_DRIVER("ACPI Opregion not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	INIT_WORK(&opregion->asle_work, psb_पूर्णांकel_opregion_asle_work);

	DRM_DEBUG("OpRegion detected at 0x%8x\n", opregion_phy);
	base = acpi_os_ioremap(opregion_phy, 8*1024);
	अगर (!base)
		वापस -ENOMEM;

	अगर (स_भेद(base, OPREGION_SIGNATURE, 16)) अणु
		DRM_DEBUG_DRIVER("opregion signature mismatch\n");
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	opregion->header = base;
	opregion->vbt = base + OPREGION_VBT_OFFSET;

	opregion->lid_state = base + ACPI_CLID;

	mboxes = opregion->header->mboxes;
	अगर (mboxes & MBOX_ACPI) अणु
		DRM_DEBUG_DRIVER("Public ACPI methods supported\n");
		opregion->acpi = base + OPREGION_ACPI_OFFSET;
	पूर्ण

	अगर (mboxes & MBOX_ASLE) अणु
		DRM_DEBUG_DRIVER("ASLE supported\n");
		opregion->asle = base + OPREGION_ASLE_OFFSET;
	पूर्ण

	वापस 0;

err_out:
	iounmap(base);
	वापस err;
पूर्ण

